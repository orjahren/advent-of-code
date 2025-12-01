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

(defn solve [file-name]
;(def input (read-file 'test-input))
  (let [lines (clojure.string/split-lines (read-file file-name))]
    (say lines)))


(solve "example")