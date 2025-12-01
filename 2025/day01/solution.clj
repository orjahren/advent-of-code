(ns solution
  (:require [clojure.string :as str]))
(defn say [what]
  (println what))
; (say "Hello from the otter slide")

(defn read-file [file-name]
  ;(say (str "Filnavnet er " file-name))
  (let [content (slurp file-name)]
    ;(println content)
    content))

; Source - https://stackoverflow.com/a/12503724
; Posted by jhnstn
; Retrieved 2025-12-01, License - CC BY-SA 3.0
(defn parse-int [s]
  (Integer. (re-find  #"\d+" s)))


(defn part1 [lines]

  (defn wrap-100 [n]
    (mod (+ n 100) 100))

  (defn rotate [direction old-state]
    ;(say (str "\t --- Direction: " direction "---"))
  ;(say (get direction 0))
    ;(println "Old state: " old-state)
    (let [distance (parse-int direction)]
      ;(say distance)
      (let [new-state (wrap-100 (if (identical? (get direction 0) \L)
                                ; TODO: Må være mulig å forenkle dette. Hente ut +/- og så applisere det generisk
                                  (- old-state distance)
                                  (+ old-state distance)))]
         new-state)))

  (let [states (reductions
                (fn [curr line]
                    ;(println 'curr "er nå" curr)
                  (rotate line curr))
                50
                lines)
        zeros (count (filter #(= 0 %) states))]

    ; (doseq [s states] (println "State:" s))
      ;(println "Final state:" (last states))
    (println states)
    (println "Part 1:" zeros)))

(defn part2 [lines]

  (defn wrap-100 [n]
    (mod (+ n 100) 100))

  (defn rotate [direction old-state]
    (say (str "\t --- Direction: " direction "---"))
  ;(say (get direction 0))
    (println "Old state: " old-state)
    (let [distance (parse-int direction)]
      (say distance)
      (let [new-state (wrap-100 (if (identical? (get direction 0) \L)
                                ; TODO: Må være mulig å forenkle dette. Hente ut +/- og så applisere det generisk
                                  (do (println "Left med dist:" distance) (- old-state distance))
                                  (do (println "Høgern med dist " distance) (+ old-state distance))))]
        (println "New state:" new-state) new-state)))

  (let [states (reductions
                (fn [curr line]
                    ;(println 'curr "er nå" curr)
                  (rotate line curr))
                50
                lines)
        zeros (count (filter #(= 0 %) states))]

    (doseq [s states] (println "State:" s))
      ;(println "Final state:" (last states))
    (println states)
    (println "Part 2:" zeros)))
 
 

(defn solve [file-name]
;(def input (read-file 'test-input))
  (let [lines (clojure.string/split-lines (read-file file-name))]
    ;(say lines)))
    ;(say "Will map lines")
    (part1 lines)))
    ;(part2 lines)))


(solve "example")
; (solve "input")