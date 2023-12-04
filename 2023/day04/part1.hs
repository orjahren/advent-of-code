import Data.Text (Text, pack, splitOn, strip, takeWhileEnd, unpack)

substringWithoutCard = takeWhileEnd (/= ':')

splitOndSpace = map (splitOn (pack " "))

getNumsOfSecondListThatAppearsInFirst :: [Int] -> [Int] -> [Int]
getNumsOfSecondListThatAppearsInFirst xs ys = [y | x <- xs, y <- ys, x == y]

getPairwiseOverlapp :: [[Int]] -> [Int]
getPairwiseOverlapp = foldl1 getNumsOfSecondListThatAppearsInFirst

getScoreRec :: [Int] -> Int -> Int
getScoreRec [] acc = acc
getScoreRec arr acc = getScoreRec (tail arr) (acc * 2)

getScore :: [Int] -> Int
getScore [] = 0
getScore [x] = 1
getScore arr = getScoreRec (tail arr) 1

main = do
  contents <- readFile "example"
  -- contents <- readFile "input"
  let input = lines contents
  let packedPipe = pack "|"
  let bits = map (splitOn packedPipe . pack) input
  let bitsWithoutCard = map (map substringWithoutCard) bits
  let stripped = map (map strip) bitsWithoutCard
  let numsAsStr = map splitOndSpace stripped
  let unpacked = map (map (map unpack)) numsAsStr
  let filtered = map (map (filter (/= ""))) unpacked
  let nums = map (map (map (read :: String -> Int))) filtered
  let overlapp = map getPairwiseOverlapp nums
  let scores = map getScore overlapp

  let finalResult = sum scores
  putStrLn "Part 1:"
  print finalResult
