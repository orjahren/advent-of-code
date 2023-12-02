{-# LANGUAGE OverloadedStrings #-}

import Data.Text (pack, replace, unpack)

getFirstNumber = take 1

getLastNumber = take 1 . reverse

concatNumbers x y = x ++ y

symbolIsNumber :: Char -> Bool
symbolIsNumber = (`elem` ("0123456789" :: String))

multiReplace :: String -> String
multiReplace str = unpack $ replace "zero" "0" $ replace "one" "1" $ replace "two" "2" $ replace "three" "3" $ replace "four" "4" $ replace "five" "5" $ replace "six" "6" $ replace "seven" "7" $ replace "eight" "8" $ replace "nine" "9" $ pack str

main = do
  content <- readFile "example2"
  -- content <- readFile "input"
  let lines = words content
  putStrLn content

  let processedLines = map multiReplace lines
  putStrLn "processedLines:"
  print processedLines
  -- extract only the numbers from every line
  let runes = map (filter symbolIsNumber) processedLines

  -- get first and last number from every line
  let firstNumbers = map getFirstNumber runes
  let lastNumbers = map getLastNumber runes

  -- concat first and last number
  let numsAsString = zipWith concatNumbers firstNumbers lastNumbers

  let nums = map read numsAsString :: [Int]

  print numsAsString
  print nums

  let res = sum nums
  print res