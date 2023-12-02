concatNumbers x y = x ++ y

symbolIsNumber = (`elem` "0123456789")

main = do
  content <- readFile "example"
  let runes = map (filter symbolIsNumber) (words content)
  let numsAsString = zipWith concatNumbers (map (take 1) runes) (map (take 1 . reverse) runes)
  let nums = map read numsAsString :: [Int]
  print (sum nums)