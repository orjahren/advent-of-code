(ns solution)
(defn say [what]
  (println what))
(say "Hello from the otter slide")

(defn read-file [file-name]
  ;(say (str "Filnavnet er " file-name))
  (let [content (slurp file-name)]
    ;(println content)
    content))

;(def input (read-file 'test-input))
(def input (read-file "test-input"))
(say input)