#! /usr/bin/env runhugs +l
--
-- Lexer.hs
-- Copyright (C) 2013 vermeille <guillaume.sanchez@epita.fr>
--
-- Distributed under terms of the MIT license.
--

module Lexer where

import Data.Char

data TokenType = TokLet
        | TokIn
        | TokEq
        | TokPlus
        | TokMinus
        | TokMul
        | TokDiv
        | TokOPar
        | TokCPar
        | TokComma
        | TokLess
        | TokMoar
        | TokLeq
        | TokMeq
        | TokVar String
        | TokNbr Int
        | TokIf
        | TokThen
        | TokElse
        | TokOBrack
        | TokCBrack
        | TokStr
        | TokEnd
        | TokSemiColon
        | TokEOF
        deriving Show

type ParseState a = Either String a

type Reader = (String, Int, Int)
type Parser a = Reader -> ParseState a

thenP :: Parser a -> (a -> Parser b) -> Parser b
m `thenP` n = \r ->
    case m r of
        Right a -> n a r
        Left a -> Left a

returnP :: a -> Parser a
returnP a = \r -> Right a

type Token = (TokenType, Int, Int)

data Located a = L (Int, Int) a
    deriving Show

lexer :: (Located TokenType -> Parser a) -> Parser a
lexer cont (str, l, c) =
    case str of
        ""         -> cont (L (0, 0) TokEOF) ("", 0, 0)
        '\n':cs    -> lexer cont (cs, l + 1, 0)
        '<':'=':cs -> cont (L (l, c) TokLeq) (cs, l, c + 2)
        '>':'=':cs -> cont (L (l, c) TokMeq) (cs, l, c + 2)
        c':cs
            | isSpace c' -> lexer  cont (cs,   l, c + 1)
            | isAlpha c' -> lexVar cont (c':cs, l, c)
            | isDigit c' -> lexNum cont (c':cs, l, c)
        sym -> lexOne cont (sym, l, c)

lexOne :: (Located TokenType -> Parser a) -> Parser a
lexOne cont (c:cs, l, col) = cont (L (l, col) (tok c)) (cs, l, col + 1)
    where
        tok '=' = TokEq
        tok '+' = TokPlus
        tok '-' = TokMinus
        tok '*' = TokMul
        tok '/' = TokDiv
        tok '(' = TokOPar
        tok ')' = TokCPar
        tok ',' = TokComma
        tok '<' = TokLess
        tok '>' = TokMoar
        tok ';' = TokSemiColon
        tok '[' = TokOBrack
        tok ']' = TokCBrack

lexVar :: (Located TokenType -> Parser a) -> Parser a
lexVar cont (cs, l, col) =
    case span isAlpha cs of
       ("let",  cs') -> cont (L (l, col) TokLet)     (cs', l, col + 3)
       ("in",   cs') -> cont (L (l, col) TokIn)      (cs', l, col + 2)
       ("end",  cs') -> cont (L (l, col) TokEnd)     (cs', l, col + 3)
       ("if",   cs') -> cont (L (l, col) TokIf)      (cs', l, col + 2)
       ("then", cs') -> cont (L (l, col) TokThen)    (cs', l, col + 4)
       ("else", cs') -> cont (L (l, col) TokElse)    (cs', l, col + 4)
       (var,    cs') -> cont (L (l, col) (TokVar var)) (cs', l, col + length var)

lexNum :: (Located TokenType -> Parser a) -> Parser a
lexNum cont (cs, l, col) =
    let nbr = read num in
        cont (L (l, col) (TokNbr nbr)) (cs', l, col + length num)
    where (num, cs') = span isDigit cs



