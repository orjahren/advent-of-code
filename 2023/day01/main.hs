getFirstNumber = take 1

getLastNumber = take 1 . reverse

-- concatNumbers :: Char -> Char -> String
-- concatNumbers x y = show x ++ show y
concatNumbers x y = x ++ y

symbolIsNumber = (`elem` "0123456789")

main = do
  content <- readFile "example"
  let lines = words content
  -- extract only the numbers from every line
  let runes = map (filter symbolIsNumber) lines

  -- get first and last number from every line
  let firstNumbers = map getFirstNumber runes
  let lastNumbers = map getLastNumber runes

  -- concat first and last number
  let runes = zipWith concatNumbers firstNumbers lastNumbers

  let nums = map read runes :: [Int]

  putStrLn content
  print runes
  print nums

  let res = sum nums
  print res