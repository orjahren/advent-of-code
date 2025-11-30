(ns aoc-25-1)
(defn say [what]
   (println what))
(say "Hello from the otter slide")

(defn read-file [file-name]
    (def content (slurp file-name))
    ;(println content)
    content)

(def input (read-file "test-input"))
(say input)