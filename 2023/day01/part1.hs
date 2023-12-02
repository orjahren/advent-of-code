concatNumbers x y = x ++ y

main = do
  content <- readFile "input"
  let runes = map (filter (`elem` "123456789")) (words content)
  let numsAsString = zipWith concatNumbers (map (take 1) runes) (map (take 1 . reverse) runes)
  print (sum (map read numsAsString :: [Int]))