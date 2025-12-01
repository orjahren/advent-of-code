(ns solution
  (:require [clojure.string :as str]))

(defn parse-int [s]
  (Integer. (re-find  #"\d+" s)))

(defn wrap-100 [n]
  (mod (+ n 100) 100))

(defn first-hit-index [curr step target]
  (if (pos? step)
    (mod (- target curr) 100)
    (mod (- curr target) 100)))

(defn count-hits [curr step distance target]
  (if (zero? distance)
    0
    (let [first-hit (first-hit-index curr step target)]
      (if (>= first-hit distance)
        0
        (inc (quot (- (dec distance) first-hit) 100))))))

(defn solve [file-name]
  (let [lines (clojure.string/split-lines (slurp file-name))
        {:keys [states  zero-count]}
        (reduce
         (fn [{:keys [curr zero-count states]} line]
           (let [distance   (parse-int line)
                 step       (if (identical? (get line 0) \L) -1 1)
                 zero-hits  (count-hits curr step distance 0)
                 final-curr (wrap-100 (+ curr (* step distance)))]
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