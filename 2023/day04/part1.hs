import Data.Text (Text, isInfixOf, pack, replace, splitOn, strip, takeWhileEnd, unpack)

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
  print input
  let packedPipe = pack "|"
  let bits = map (splitOn packedPipe . pack) input
  print bits
  let bitsWithoutCard = map (map substringWithoutCard) bits
  putStrLn "bitsWithoutCard"
  print bitsWithoutCard
  let stripped = map (map strip) bitsWithoutCard
  putStrLn "stripped"
  print stripped

  putStrLn "numsAsStr"
  let numsAsStr = map splitOndSpace stripped
  print numsAsStr

  putStrLn "unpacked"
  let unpacked = map (map (map unpack)) numsAsStr
  print unpacked

  let filtered = map (map (filter (/= ""))) unpacked
  putStrLn "filtered"
  print filtered

  let nums = map (map (map (read :: String -> Int))) filtered
  putStrLn "nums"
  print nums

  putStrLn "overlapp"
  let overlapp = map getPairwiseOverlapp nums
  print overlapp

  let scores = map getScore overlapp
  putStrLn "Scores"
  print scores

  let finalResult = sum scores
  putStrLn "Part 1:"
  print finalResult
