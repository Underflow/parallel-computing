module Main where

import Parser
import Lexer
import Eval

main = do txt <- getContents
          let ast = parse (txt, 0, 0)
          -- print $ map typeFunDec ast
          print ast
          return ()

