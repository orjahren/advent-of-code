import Data.Text (isInfixOf, pack, replace, splitOn, strip, takeWhileEnd, unpack)

-- removeCard :: String -> String
-- removeCard [] = []
-- removeCard (x : xs) = if pack "Card" `isInfixOf` x then xs else removeCard xs
-- removeCard = takeWhileEnd /= pack ":"
-- substringWithoutCard :: String -> String
substringWithoutCard = takeWhileEnd (/= ':')

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
