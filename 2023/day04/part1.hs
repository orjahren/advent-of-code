main = do
  contents <- readFile "example"
  -- contents <- readFile "input"
  let input = lines contents
  print input