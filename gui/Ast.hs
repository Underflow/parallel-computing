#! /usr/bin/env runhugs +l
--
-- Ast.hs
-- Copyright (C) 2013 vermeille <guillaume.sanchez@epita.fr>
--
-- Distributed under terms of the MIT license.
--

module Ast where

data Exp = Add Exp Exp
         | Sub Exp Exp
         | Div Exp Exp
         | Mul Exp Exp
         | Less Exp Exp
         | Great Exp Exp
         | Leq Exp Exp
         | Geq Exp Exp
         | If Exp Exp Exp
         | Var String
         | ListLit [Exp]
         | Let [([String], Exp)] Exp
         | Nbr Int
         | Paren Exp
         deriving Show


