#! /usr/bin/env runhugs +l
--
-- Eval.hs
-- Copyright (C) 2013 vermeille <guillaume.sanchez@epita.fr>
--
-- Distributed under terms of the MIT license.
--

module Eval where

import Ast
import Data.List

data Type = TNbr
          | TStr
          | TList Type
          | TBool
          | TPoly
          deriving (Eq, Show)

type Typed = (String, Type)

isLeft  = either (const True) (const False)
isRight = either (const False) (const True)

typeCheck :: [Typed] -> Exp -> Either Type Exp

typeCheck env (Var a) =
    case find ((== a) . fst) env of
        Just res -> Left $ snd res
        Nothing -> Right (Var a)

typeCheck env (Nbr a) = Left TNbr

typeCheck env exp@(Add a b) =
    case (typeCheck env a, typeCheck env b) of
        (Left a, Left b) -> mergeTy a b
        _ -> Right $ exp

typeCheck env exp@(Sub a b) =
    case (typeCheck env a, typeCheck env b) of
        (Left a, Left b) -> mergeTy a b
        _ -> Right $ exp

typeCheck env (Mul a b) =
    case (typeCheck env a, typeCheck env b) of
        (Left a, Left b) -> mergeTy a b
        _ -> Right $ Add a b

typeCheck env (Div a b) =
    case (typeCheck env a, typeCheck env b) of
        (Left a, Left b) -> mergeTy a b
        _ -> Right $ Add a b

typeCheck env (Less a b) =
    case (typeCheck env a, typeCheck env b) of
        (Left TNbr, Left TNbr) -> Left TBool
        _ -> Right $ Less a b

typeCheck env (Great a b) =
    case (typeCheck env a, typeCheck env b) of
        (Left TNbr, Left TNbr) -> Left TBool
        _ -> Right $ Less a b

typeCheck env (Leq a b) =
    case (typeCheck env a, typeCheck env b) of
        (Left TNbr, Left TNbr) -> Left TBool
        _ -> Right $ Less a b

typeCheck env (Geq a b) =
    case (typeCheck env a, typeCheck env b) of
        (Left TNbr, Left TNbr) -> Left TBool
        _ -> Right $ Less a b

typeCheck env (ListLit [a]) = typeCheck env a

typeCheck env (ListLit (a:as)) =
        case (typeCheck env a, typeCheck env (ListLit as)) of
            (Left a, Left b) -> mergeTy a b
            _                -> Right (ListLit (a:as))

typeCheck env (Paren a) = typeCheck env a

typeCheck env (Let a b) =
    let decs = map (typePair env) a in
            typeCheck (decs ++ env) b
    where typePair env =
            (\(x, y) -> (head x, purify $ typeCheck env y))
          purify = either id undefined

typeCheck env (If a b c) =
    case (tIf, tElse, tThen) of
        (Left a, Left b, Left c) | a == b && b == c -> Left b
        _ -> Right $ If a b c
    where [tIf, tThen, tElse] = map (typeCheck env) [a, b, c]

typeFunDec :: ([String], Exp) -> Either Type Exp
typeFunDec decs = typeCheck (map (\x -> (x, TPoly)) $ fst decs) $ snd decs

mergeTy :: Type -> Type -> Either Type Exp

mergeTy TPoly TPoly = Left TPoly
mergeTy TNbr TNbr = Left TNbr
mergeTy TStr TStr = Left TStr
mergeTy TBool TBool = Left TBool
mergeTy (TList t) (TList t') = mergeTy t t'
mergeTy t TPoly = Left t
mergeTy TPoly t = Left t

mergeTy _ _ = Right $ Var "error"

