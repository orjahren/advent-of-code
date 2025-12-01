(ns solution
  (:require [clojure.string :as str]))

(defn solve [file-name]
  (let [lines (str/split-lines (slurp file-name))
        {:keys [states zero-count]}
        (reduce
         (fn [{:keys [curr zero-count states]} line]
           (let [distance (Integer. (re-find #"\d+" line))
                 step     (if (= (first line) \L) -1 1)
                 first-hit (if (pos? step)
                             (mod (- 0 curr) 100)
                             (mod (- curr 0) 100))
                 zero-hits (if (or (zero? distance) (>= first-hit distance))
                             0
                             (inc (quot (- (dec distance) first-hit) 100)))
                 final-curr (mod (+ curr (* step distance) 100) 100)]
             {:curr final-curr
              :zero-count (+ zero-count zero-hits)
              :states (conj states final-curr)}))
         {:curr 50 :zero-count 0 :states [50]}
         lines)]
    (println states)
    (println "Part 1:" (count (filter zero? states)))
    (println "Part 2:" zero-count)))

;(solve "example")
(solve "input")