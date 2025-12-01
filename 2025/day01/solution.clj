(ns solution
  (:require [clojure.string :as str]))
(defn say [what]
  (println what))
(say "Hello from the otter slide")

(defn read-file [file-name]
  ;(say (str "Filnavnet er " file-name))
  (let [content (slurp file-name)]
    ;(println content)
    content))


;(defn rotate [direction old-state new-state]
(defn rotate [direction]
  (say (str "Direction: " direction))
  ;(say (get direction 0))
  (let [distance (subs direction 1)]
    ;(say distance)
    (if (identical? (get direction 0) \L) (say (str "Left med dist: " distance)) (say (str "Høgern med dist " distance))))
  direction)

(defn solve [file-name]
;(def input (read-file 'test-input))
  (let [lines (clojure.string/split-lines (read-file file-name))]
    ;(say lines)))
    (say "Will map lines")
    (let [curr 50])
    (let [new-state (map rotate lines)] (say new-state))))


(solve "example")