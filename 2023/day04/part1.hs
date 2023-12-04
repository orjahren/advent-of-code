import Data.Text (Text, pack, splitOn, strip, takeWhileEnd, unpack)

substringWithoutCard = takeWhileEnd (/= ':')

splitOndSpace = map (splitOn (pack " "))

getNumbersThatAppearsInBothLists :: [Int] -> [Int] -> [Int]
getNumbersThatAppearsInBothLists xs ys = [x | x <- xs, y <- ys, x == y]

getScoreRec :: [Int] -> Int -> Int
getScoreRec [] acc = acc
getScoreRec arr acc = getScoreRec (tail arr) (acc * 2)

getScore :: [Int] -> Int
getScore [] = 0
getScore [x] = 1
getScore arr = getScoreRec (tail arr) 1

main = do
  -- contents <- readFile "example"
  input <- readFile "input"
  let bits = map (splitOn (pack "|") . pack) (lines input)
  let bitsWithoutCard = map (map substringWithoutCard) bits
  let stripped = map (map strip) bitsWithoutCard
  let numsAsStr = map splitOndSpace stripped
  let unpacked = map (map (map unpack)) numsAsStr
  let filtered = map (map (filter (/= ""))) unpacked
  let nums = map (map (map (read :: String -> Int))) filtered
  let overlapp = map (foldl1 getNumbersThatAppearsInBothLists) nums
  let scores = map getScore overlapp

  putStrLn "Part 1:"
  print (sum scores)
