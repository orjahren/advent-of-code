(ns solution
  (:require [clojure.string :as str]))

(defn parse-int [s]
  (Integer. (re-find  #"\d+" s)))

(defn solve [file-name]
  (let [lines (clojure.string/split-lines (slurp file-name))
        {:keys [states wrap-count]}
        (reduce
         (fn [{:keys [curr wrap-count states]} line]
           (let [distance (parse-int line)
                 delta    (if (identical? (get line 0) \L) (- distance) distance)
                 next     (+ curr delta)
                 wraps    (Math/abs (Math/floorDiv next 100))
                 wrapped  (mod next 100)]
             {:curr wrapped
              :wrap-count (+ wrap-count wraps)
              :states (conj states wrapped)}))
         {:curr 50 :wrap-count 0 :states [50]}
         lines)]
    (println states)
    (println "Part 1:" (count (filter zero? states)))
    (println "Part 2:" wrap-count)))
      ; p2: 6580 too high


;(solve "example")
(solve "input")