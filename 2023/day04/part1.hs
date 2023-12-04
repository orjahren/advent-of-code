import Data.Text (Text, isInfixOf, pack, replace, splitOn, strip, takeWhileEnd, unpack)

-- removeCard :: String -> String
-- removeCard [] = []
-- removeCard (x : xs) = if pack "Card" `isInfixOf` x then xs else removeCard xs
-- removeCard = takeWhileEnd /= pack ":"
-- substringWithoutCard :: String -> String
substringWithoutCard = takeWhileEnd (/= ':')

-- splitAndConvert :: [Text] -> [Int]
-- splitAndConvertToInt = map (read . unpack)
splitOndSpace = map (splitOn (pack " "))

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

  -- let nums = map (map (map (read :: Int))) numsAsStr
  -- let nums = map (map (map (read :: String -> Int))) unpacked
  let nums = map (map (map (read :: String -> Int))) filtered
  putStrLn "nums"
  print nums

-- print nums
-- let x = show nums
-- print x
