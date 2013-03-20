{-# OPTIONS_GHC -w #-}
module Parser where

import Data.Char
import Prelude
import Ast
import Lexer

-- parser produced by Happy Version 1.18.10

data HappyAbsSyn t4 t5 t6 t7 t8 t9 t10
	= HappyTerminal (Located TokenType)
	| HappyErrorToken Int
	| HappyAbsSyn4 t4
	| HappyAbsSyn5 t5
	| HappyAbsSyn6 t6
	| HappyAbsSyn7 t7
	| HappyAbsSyn8 t8
	| HappyAbsSyn9 t9
	| HappyAbsSyn10 t10

action_0 (4) = happyGoto action_3
action_0 (5) = happyGoto action_2
action_0 _ = happyReduce_3

action_1 (5) = happyGoto action_2
action_1 _ = happyFail

action_2 (25) = happyShift action_6
action_2 (34) = happyReduce_1
action_2 (6) = happyGoto action_4
action_2 (7) = happyGoto action_5
action_2 _ = happyReduce_6

action_3 (34) = happyAccept
action_3 _ = happyFail

action_4 _ = happyReduce_2

action_5 (13) = happyShift action_8
action_5 _ = happyFail

action_6 (25) = happyShift action_6
action_6 (7) = happyGoto action_7
action_6 _ = happyReduce_6

action_7 _ = happyReduce_5

action_8 (11) = happyShift action_11
action_8 (18) = happyShift action_12
action_8 (25) = happyShift action_13
action_8 (26) = happyShift action_14
action_8 (27) = happyShift action_15
action_8 (31) = happyShift action_16
action_8 (8) = happyGoto action_9
action_8 (9) = happyGoto action_10
action_8 _ = happyFail

action_9 (14) = happyShift action_22
action_9 (15) = happyShift action_23
action_9 (16) = happyShift action_24
action_9 (17) = happyShift action_25
action_9 (21) = happyShift action_26
action_9 (22) = happyShift action_27
action_9 (23) = happyShift action_28
action_9 (24) = happyShift action_29
action_9 _ = happyReduce_4

action_10 _ = happyReduce_18

action_11 (5) = happyGoto action_21
action_11 _ = happyReduce_3

action_12 (11) = happyShift action_11
action_12 (18) = happyShift action_12
action_12 (25) = happyShift action_13
action_12 (26) = happyShift action_14
action_12 (27) = happyShift action_15
action_12 (31) = happyShift action_16
action_12 (8) = happyGoto action_20
action_12 (9) = happyGoto action_10
action_12 _ = happyFail

action_13 _ = happyReduce_7

action_14 _ = happyReduce_20

action_15 (11) = happyShift action_11
action_15 (18) = happyShift action_12
action_15 (25) = happyShift action_13
action_15 (26) = happyShift action_14
action_15 (27) = happyShift action_15
action_15 (31) = happyShift action_16
action_15 (8) = happyGoto action_19
action_15 (9) = happyGoto action_10
action_15 _ = happyFail

action_16 (11) = happyShift action_11
action_16 (18) = happyShift action_12
action_16 (25) = happyShift action_13
action_16 (26) = happyShift action_14
action_16 (27) = happyShift action_15
action_16 (31) = happyShift action_16
action_16 (8) = happyGoto action_17
action_16 (9) = happyGoto action_10
action_16 (10) = happyGoto action_18
action_16 _ = happyFail

action_17 (14) = happyShift action_22
action_17 (15) = happyShift action_23
action_17 (16) = happyShift action_24
action_17 (17) = happyShift action_25
action_17 (20) = happyShift action_42
action_17 (21) = happyShift action_26
action_17 (22) = happyShift action_27
action_17 (23) = happyShift action_28
action_17 (24) = happyShift action_29
action_17 _ = happyReduce_23

action_18 (32) = happyShift action_41
action_18 _ = happyFail

action_19 (14) = happyShift action_22
action_19 (15) = happyShift action_23
action_19 (16) = happyShift action_24
action_19 (17) = happyShift action_25
action_19 (21) = happyShift action_26
action_19 (22) = happyShift action_27
action_19 (23) = happyShift action_28
action_19 (24) = happyShift action_29
action_19 (28) = happyShift action_40
action_19 _ = happyFail

action_20 (14) = happyShift action_22
action_20 (15) = happyShift action_23
action_20 (16) = happyShift action_24
action_20 (17) = happyShift action_25
action_20 (19) = happyShift action_39
action_20 (21) = happyShift action_26
action_20 (22) = happyShift action_27
action_20 (23) = happyShift action_28
action_20 (24) = happyShift action_29
action_20 _ = happyFail

action_21 (12) = happyShift action_38
action_21 (25) = happyShift action_6
action_21 (6) = happyGoto action_4
action_21 (7) = happyGoto action_5
action_21 _ = happyReduce_6

action_22 (11) = happyShift action_11
action_22 (18) = happyShift action_12
action_22 (25) = happyShift action_13
action_22 (26) = happyShift action_14
action_22 (27) = happyShift action_15
action_22 (31) = happyShift action_16
action_22 (8) = happyGoto action_37
action_22 (9) = happyGoto action_10
action_22 _ = happyFail

action_23 (11) = happyShift action_11
action_23 (18) = happyShift action_12
action_23 (25) = happyShift action_13
action_23 (26) = happyShift action_14
action_23 (27) = happyShift action_15
action_23 (31) = happyShift action_16
action_23 (8) = happyGoto action_36
action_23 (9) = happyGoto action_10
action_23 _ = happyFail

action_24 (11) = happyShift action_11
action_24 (18) = happyShift action_12
action_24 (25) = happyShift action_13
action_24 (26) = happyShift action_14
action_24 (27) = happyShift action_15
action_24 (31) = happyShift action_16
action_24 (8) = happyGoto action_35
action_24 (9) = happyGoto action_10
action_24 _ = happyFail

action_25 (11) = happyShift action_11
action_25 (18) = happyShift action_12
action_25 (25) = happyShift action_13
action_25 (26) = happyShift action_14
action_25 (27) = happyShift action_15
action_25 (31) = happyShift action_16
action_25 (8) = happyGoto action_34
action_25 (9) = happyGoto action_10
action_25 _ = happyFail

action_26 (11) = happyShift action_11
action_26 (18) = happyShift action_12
action_26 (25) = happyShift action_13
action_26 (26) = happyShift action_14
action_26 (27) = happyShift action_15
action_26 (31) = happyShift action_16
action_26 (8) = happyGoto action_33
action_26 (9) = happyGoto action_10
action_26 _ = happyFail

action_27 (11) = happyShift action_11
action_27 (18) = happyShift action_12
action_27 (25) = happyShift action_13
action_27 (26) = happyShift action_14
action_27 (27) = happyShift action_15
action_27 (31) = happyShift action_16
action_27 (8) = happyGoto action_32
action_27 (9) = happyGoto action_10
action_27 _ = happyFail

action_28 (11) = happyShift action_11
action_28 (18) = happyShift action_12
action_28 (25) = happyShift action_13
action_28 (26) = happyShift action_14
action_28 (27) = happyShift action_15
action_28 (31) = happyShift action_16
action_28 (8) = happyGoto action_31
action_28 (9) = happyGoto action_10
action_28 _ = happyFail

action_29 (11) = happyShift action_11
action_29 (18) = happyShift action_12
action_29 (25) = happyShift action_13
action_29 (26) = happyShift action_14
action_29 (27) = happyShift action_15
action_29 (31) = happyShift action_16
action_29 (8) = happyGoto action_30
action_29 (9) = happyGoto action_10
action_29 _ = happyFail

action_30 (14) = happyShift action_22
action_30 (15) = happyShift action_23
action_30 (16) = happyShift action_24
action_30 (17) = happyShift action_25
action_30 _ = happyReduce_15

action_31 (14) = happyShift action_22
action_31 (15) = happyShift action_23
action_31 (16) = happyShift action_24
action_31 (17) = happyShift action_25
action_31 _ = happyReduce_14

action_32 (14) = happyShift action_22
action_32 (15) = happyShift action_23
action_32 (16) = happyShift action_24
action_32 (17) = happyShift action_25
action_32 _ = happyReduce_13

action_33 (14) = happyShift action_22
action_33 (15) = happyShift action_23
action_33 (16) = happyShift action_24
action_33 (17) = happyShift action_25
action_33 _ = happyReduce_12

action_34 _ = happyReduce_10

action_35 _ = happyReduce_11

action_36 (16) = happyShift action_24
action_36 (17) = happyShift action_25
action_36 _ = happyReduce_9

action_37 (16) = happyShift action_24
action_37 (17) = happyShift action_25
action_37 _ = happyReduce_8

action_38 (11) = happyShift action_11
action_38 (18) = happyShift action_12
action_38 (25) = happyShift action_13
action_38 (26) = happyShift action_14
action_38 (27) = happyShift action_15
action_38 (31) = happyShift action_16
action_38 (8) = happyGoto action_45
action_38 (9) = happyGoto action_10
action_38 _ = happyFail

action_39 _ = happyReduce_16

action_40 (11) = happyShift action_11
action_40 (18) = happyShift action_12
action_40 (25) = happyShift action_13
action_40 (26) = happyShift action_14
action_40 (27) = happyShift action_15
action_40 (31) = happyShift action_16
action_40 (8) = happyGoto action_44
action_40 (9) = happyGoto action_10
action_40 _ = happyFail

action_41 _ = happyReduce_21

action_42 (11) = happyShift action_11
action_42 (18) = happyShift action_12
action_42 (25) = happyShift action_13
action_42 (26) = happyShift action_14
action_42 (27) = happyShift action_15
action_42 (31) = happyShift action_16
action_42 (8) = happyGoto action_17
action_42 (9) = happyGoto action_10
action_42 (10) = happyGoto action_43
action_42 _ = happyFail

action_43 _ = happyReduce_22

action_44 (14) = happyShift action_22
action_44 (15) = happyShift action_23
action_44 (16) = happyShift action_24
action_44 (17) = happyShift action_25
action_44 (21) = happyShift action_26
action_44 (22) = happyShift action_27
action_44 (23) = happyShift action_28
action_44 (24) = happyShift action_29
action_44 (29) = happyShift action_47
action_44 _ = happyFail

action_45 (14) = happyShift action_22
action_45 (15) = happyShift action_23
action_45 (16) = happyShift action_24
action_45 (17) = happyShift action_25
action_45 (21) = happyShift action_26
action_45 (22) = happyShift action_27
action_45 (23) = happyShift action_28
action_45 (24) = happyShift action_29
action_45 (30) = happyShift action_46
action_45 _ = happyFail

action_46 _ = happyReduce_19

action_47 (11) = happyShift action_11
action_47 (18) = happyShift action_12
action_47 (25) = happyShift action_13
action_47 (26) = happyShift action_14
action_47 (27) = happyShift action_15
action_47 (31) = happyShift action_16
action_47 (8) = happyGoto action_48
action_47 (9) = happyGoto action_10
action_47 _ = happyFail

action_48 (14) = happyShift action_22
action_48 (15) = happyShift action_23
action_48 (16) = happyShift action_24
action_48 (17) = happyShift action_25
action_48 (21) = happyShift action_26
action_48 (22) = happyShift action_27
action_48 (23) = happyShift action_28
action_48 (24) = happyShift action_29
action_48 _ = happyReduce_17

happyReduce_1 = happySpecReduce_1  4 happyReduction_1
happyReduction_1 (HappyAbsSyn5  happy_var_1)
	 =  HappyAbsSyn4
		 (happy_var_1
	)
happyReduction_1 _  = notHappyAtAll 

happyReduce_2 = happySpecReduce_2  5 happyReduction_2
happyReduction_2 (HappyAbsSyn6  happy_var_2)
	(HappyAbsSyn5  happy_var_1)
	 =  HappyAbsSyn5
		 (happy_var_2:happy_var_1
	)
happyReduction_2 _ _  = notHappyAtAll 

happyReduce_3 = happySpecReduce_0  5 happyReduction_3
happyReduction_3  =  HappyAbsSyn5
		 ([]
	)

happyReduce_4 = happySpecReduce_3  6 happyReduction_4
happyReduction_4 (HappyAbsSyn8  happy_var_3)
	_
	(HappyAbsSyn7  happy_var_1)
	 =  HappyAbsSyn6
		 ((happy_var_1, happy_var_3)
	)
happyReduction_4 _ _ _  = notHappyAtAll 

happyReduce_5 = happySpecReduce_2  7 happyReduction_5
happyReduction_5 (HappyAbsSyn7  happy_var_2)
	(HappyTerminal (L _ (TokVar happy_var_1)))
	 =  HappyAbsSyn7
		 (happy_var_1:happy_var_2
	)
happyReduction_5 _ _  = notHappyAtAll 

happyReduce_6 = happySpecReduce_0  7 happyReduction_6
happyReduction_6  =  HappyAbsSyn7
		 ([]
	)

happyReduce_7 = happySpecReduce_1  8 happyReduction_7
happyReduction_7 (HappyTerminal (L _ (TokVar happy_var_1)))
	 =  HappyAbsSyn8
		 (Var happy_var_1
	)
happyReduction_7 _  = notHappyAtAll 

happyReduce_8 = happySpecReduce_3  8 happyReduction_8
happyReduction_8 (HappyAbsSyn8  happy_var_3)
	_
	(HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn8
		 (Add happy_var_1 happy_var_3
	)
happyReduction_8 _ _ _  = notHappyAtAll 

happyReduce_9 = happySpecReduce_3  8 happyReduction_9
happyReduction_9 (HappyAbsSyn8  happy_var_3)
	_
	(HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn8
		 (Sub happy_var_1 happy_var_3
	)
happyReduction_9 _ _ _  = notHappyAtAll 

happyReduce_10 = happySpecReduce_3  8 happyReduction_10
happyReduction_10 (HappyAbsSyn8  happy_var_3)
	_
	(HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn8
		 (Div happy_var_1 happy_var_3
	)
happyReduction_10 _ _ _  = notHappyAtAll 

happyReduce_11 = happySpecReduce_3  8 happyReduction_11
happyReduction_11 (HappyAbsSyn8  happy_var_3)
	_
	(HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn8
		 (Mul happy_var_1 happy_var_3
	)
happyReduction_11 _ _ _  = notHappyAtAll 

happyReduce_12 = happySpecReduce_3  8 happyReduction_12
happyReduction_12 (HappyAbsSyn8  happy_var_3)
	_
	(HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn8
		 (Less happy_var_1 happy_var_3
	)
happyReduction_12 _ _ _  = notHappyAtAll 

happyReduce_13 = happySpecReduce_3  8 happyReduction_13
happyReduction_13 (HappyAbsSyn8  happy_var_3)
	_
	(HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn8
		 (Great happy_var_1 happy_var_3
	)
happyReduction_13 _ _ _  = notHappyAtAll 

happyReduce_14 = happySpecReduce_3  8 happyReduction_14
happyReduction_14 (HappyAbsSyn8  happy_var_3)
	_
	(HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn8
		 (Leq happy_var_1 happy_var_3
	)
happyReduction_14 _ _ _  = notHappyAtAll 

happyReduce_15 = happySpecReduce_3  8 happyReduction_15
happyReduction_15 (HappyAbsSyn8  happy_var_3)
	_
	(HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn8
		 (Geq happy_var_1 happy_var_3
	)
happyReduction_15 _ _ _  = notHappyAtAll 

happyReduce_16 = happySpecReduce_3  8 happyReduction_16
happyReduction_16 _
	(HappyAbsSyn8  happy_var_2)
	_
	 =  HappyAbsSyn8
		 (Paren happy_var_2
	)
happyReduction_16 _ _ _  = notHappyAtAll 

happyReduce_17 = happyReduce 6 8 happyReduction_17
happyReduction_17 ((HappyAbsSyn8  happy_var_6) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn8  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn8  happy_var_2) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn8
		 (If happy_var_2 happy_var_4 happy_var_6
	) `HappyStk` happyRest

happyReduce_18 = happySpecReduce_1  8 happyReduction_18
happyReduction_18 (HappyAbsSyn9  happy_var_1)
	 =  HappyAbsSyn8
		 (ListLit happy_var_1
	)
happyReduction_18 _  = notHappyAtAll 

happyReduce_19 = happyReduce 5 8 happyReduction_19
happyReduction_19 (_ `HappyStk`
	(HappyAbsSyn8  happy_var_4) `HappyStk`
	_ `HappyStk`
	(HappyAbsSyn5  happy_var_2) `HappyStk`
	_ `HappyStk`
	happyRest)
	 = HappyAbsSyn8
		 (Let happy_var_2 happy_var_4
	) `HappyStk` happyRest

happyReduce_20 = happySpecReduce_1  8 happyReduction_20
happyReduction_20 (HappyTerminal (L _ (TokNbr happy_var_1)))
	 =  HappyAbsSyn8
		 (Nbr happy_var_1
	)
happyReduction_20 _  = notHappyAtAll 

happyReduce_21 = happySpecReduce_3  9 happyReduction_21
happyReduction_21 _
	(HappyAbsSyn10  happy_var_2)
	_
	 =  HappyAbsSyn9
		 (happy_var_2
	)
happyReduction_21 _ _ _  = notHappyAtAll 

happyReduce_22 = happySpecReduce_3  10 happyReduction_22
happyReduction_22 (HappyAbsSyn10  happy_var_3)
	_
	(HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn10
		 (happy_var_1:happy_var_3
	)
happyReduction_22 _ _ _  = notHappyAtAll 

happyReduce_23 = happySpecReduce_1  10 happyReduction_23
happyReduction_23 (HappyAbsSyn8  happy_var_1)
	 =  HappyAbsSyn10
		 ([happy_var_1]
	)
happyReduction_23 _  = notHappyAtAll 

happyNewToken action sts stk
	= lexer(\tk -> 
	let cont i = action i i tk (HappyState action) sts stk in
	case tk of {
	L _ TokEOF -> action 34 34 tk (HappyState action) sts stk;
	L _ TokLet -> cont 11;
	L _ TokIn -> cont 12;
	L _ TokEq -> cont 13;
	L _ TokPlus -> cont 14;
	L _ TokMinus -> cont 15;
	L _ TokMul -> cont 16;
	L _ TokDiv -> cont 17;
	L _ TokOPar -> cont 18;
	L _ TokCPar -> cont 19;
	L _ TokComma -> cont 20;
	L _ TokLess -> cont 21;
	L _ TokMoar -> cont 22;
	L _ TokLeq -> cont 23;
	L _ TokMeq -> cont 24;
	L _ (TokVar happy_dollar_dollar) -> cont 25;
	L _ (TokNbr happy_dollar_dollar) -> cont 26;
	L _ TokIf -> cont 27;
	L _ TokThen -> cont 28;
	L _ TokElse -> cont 29;
	L _ TokEnd -> cont 30;
	L _ TokOBrack -> cont 31;
	L _ TokCBrack -> cont 32;
	L _ TokSemiColon -> cont 33;
	_ -> happyError' tk
	})

happyError_ 34 tk = happyError' tk
happyError_ _ tk = happyError' tk

happyThen :: () => Parser a -> (a -> Parser b) -> Parser b
happyThen = (thenP)
happyReturn :: () => a -> Parser a
happyReturn = (returnP)
happyThen1 = happyThen
happyReturn1 :: () => a -> Parser a
happyReturn1 = happyReturn
happyError' :: () => (Located TokenType) -> Parser a
happyError' tk = parseError tk

parse = happySomeParser where
  happySomeParser = happyThen (happyParse action_0) (\x -> case x of {HappyAbsSyn4 z -> happyReturn z; _other -> notHappyAtAll })

happySeq = happyDontSeq


parseError :: Located TokenType -> Parser a
parseError tok (s, l, c) = fail $ "parse error at `" ++ show (take 10 s)
    ++ "' line " ++ show l ++ " on token: " ++ show tok
{-# LINE 1 "templates/GenericTemplate.hs" #-}
{-# LINE 1 "templates/GenericTemplate.hs" #-}
{-# LINE 1 "<command-line>" #-}
{-# LINE 1 "templates/GenericTemplate.hs" #-}
-- Id: GenericTemplate.hs,v 1.26 2005/01/14 14:47:22 simonmar Exp 

{-# LINE 30 "templates/GenericTemplate.hs" #-}








{-# LINE 51 "templates/GenericTemplate.hs" #-}

{-# LINE 61 "templates/GenericTemplate.hs" #-}

{-# LINE 70 "templates/GenericTemplate.hs" #-}

infixr 9 `HappyStk`
data HappyStk a = HappyStk a (HappyStk a)

-----------------------------------------------------------------------------
-- starting the parse

happyParse start_state = happyNewToken start_state notHappyAtAll notHappyAtAll

-----------------------------------------------------------------------------
-- Accepting the parse

-- If the current token is (1), it means we've just accepted a partial
-- parse (a %partial parser).  We must ignore the saved token on the top of
-- the stack in this case.
happyAccept (1) tk st sts (_ `HappyStk` ans `HappyStk` _) =
	happyReturn1 ans
happyAccept j tk st sts (HappyStk ans _) = 
	 (happyReturn1 ans)

-----------------------------------------------------------------------------
-- Arrays only: do the next action

{-# LINE 148 "templates/GenericTemplate.hs" #-}

-----------------------------------------------------------------------------
-- HappyState data type (not arrays)



newtype HappyState b c = HappyState
        (Int ->                    -- token number
         Int ->                    -- token number (yes, again)
         b ->                           -- token semantic value
         HappyState b c ->              -- current state
         [HappyState b c] ->            -- state stack
         c)



-----------------------------------------------------------------------------
-- Shifting a token

happyShift new_state (1) tk st sts stk@(x `HappyStk` _) =
     let (i) = (case x of { HappyErrorToken (i) -> i }) in
--     trace "shifting the error token" $
     new_state i i tk (HappyState (new_state)) ((st):(sts)) (stk)

happyShift new_state i tk st sts stk =
     happyNewToken new_state ((st):(sts)) ((HappyTerminal (tk))`HappyStk`stk)

-- happyReduce is specialised for the common cases.

happySpecReduce_0 i fn (1) tk st sts stk
     = happyFail (1) tk st sts stk
happySpecReduce_0 nt fn j tk st@((HappyState (action))) sts stk
     = action nt j tk st ((st):(sts)) (fn `HappyStk` stk)

happySpecReduce_1 i fn (1) tk st sts stk
     = happyFail (1) tk st sts stk
happySpecReduce_1 nt fn j tk _ sts@(((st@(HappyState (action))):(_))) (v1`HappyStk`stk')
     = let r = fn v1 in
       happySeq r (action nt j tk st sts (r `HappyStk` stk'))

happySpecReduce_2 i fn (1) tk st sts stk
     = happyFail (1) tk st sts stk
happySpecReduce_2 nt fn j tk _ ((_):(sts@(((st@(HappyState (action))):(_))))) (v1`HappyStk`v2`HappyStk`stk')
     = let r = fn v1 v2 in
       happySeq r (action nt j tk st sts (r `HappyStk` stk'))

happySpecReduce_3 i fn (1) tk st sts stk
     = happyFail (1) tk st sts stk
happySpecReduce_3 nt fn j tk _ ((_):(((_):(sts@(((st@(HappyState (action))):(_))))))) (v1`HappyStk`v2`HappyStk`v3`HappyStk`stk')
     = let r = fn v1 v2 v3 in
       happySeq r (action nt j tk st sts (r `HappyStk` stk'))

happyReduce k i fn (1) tk st sts stk
     = happyFail (1) tk st sts stk
happyReduce k nt fn j tk st sts stk
     = case happyDrop (k - ((1) :: Int)) sts of
	 sts1@(((st1@(HappyState (action))):(_))) ->
        	let r = fn stk in  -- it doesn't hurt to always seq here...
       		happyDoSeq r (action nt j tk st1 sts1 r)

happyMonadReduce k nt fn (1) tk st sts stk
     = happyFail (1) tk st sts stk
happyMonadReduce k nt fn j tk st sts stk =
        happyThen1 (fn stk tk) (\r -> action nt j tk st1 sts1 (r `HappyStk` drop_stk))
       where (sts1@(((st1@(HappyState (action))):(_)))) = happyDrop k ((st):(sts))
             drop_stk = happyDropStk k stk

happyMonad2Reduce k nt fn (1) tk st sts stk
     = happyFail (1) tk st sts stk
happyMonad2Reduce k nt fn j tk st sts stk =
       happyThen1 (fn stk tk) (\r -> happyNewToken new_state sts1 (r `HappyStk` drop_stk))
       where (sts1@(((st1@(HappyState (action))):(_)))) = happyDrop k ((st):(sts))
             drop_stk = happyDropStk k stk





             new_state = action


happyDrop (0) l = l
happyDrop n ((_):(t)) = happyDrop (n - ((1) :: Int)) t

happyDropStk (0) l = l
happyDropStk n (x `HappyStk` xs) = happyDropStk (n - ((1)::Int)) xs

-----------------------------------------------------------------------------
-- Moving to a new state after a reduction

{-# LINE 246 "templates/GenericTemplate.hs" #-}
happyGoto action j tk st = action j j tk (HappyState action)


-----------------------------------------------------------------------------
-- Error recovery ((1) is the error token)

-- parse error if we are in recovery and we fail again
happyFail (1) tk old_st _ stk@(x `HappyStk` _) =
     let (i) = (case x of { HappyErrorToken (i) -> i }) in
--	trace "failing" $ 
        happyError_ i tk

{-  We don't need state discarding for our restricted implementation of
    "error".  In fact, it can cause some bogus parses, so I've disabled it
    for now --SDM

-- discard a state
happyFail  (1) tk old_st (((HappyState (action))):(sts)) 
						(saved_tok `HappyStk` _ `HappyStk` stk) =
--	trace ("discarding state, depth " ++ show (length stk))  $
	action (1) (1) tk (HappyState (action)) sts ((saved_tok`HappyStk`stk))
-}

-- Enter error recovery: generate an error token,
--                       save the old token and carry on.
happyFail  i tk (HappyState (action)) sts stk =
--      trace "entering error recovery" $
	action (1) (1) tk (HappyState (action)) sts ( (HappyErrorToken (i)) `HappyStk` stk)

-- Internal happy errors:

notHappyAtAll :: a
notHappyAtAll = error "Internal Happy error\n"

-----------------------------------------------------------------------------
-- Hack to get the typechecker to accept our action functions







-----------------------------------------------------------------------------
-- Seq-ing.  If the --strict flag is given, then Happy emits 
--	happySeq = happyDoSeq
-- otherwise it emits
-- 	happySeq = happyDontSeq

happyDoSeq, happyDontSeq :: a -> b -> b
happyDoSeq   a b = a `seq` b
happyDontSeq a b = b

-----------------------------------------------------------------------------
-- Don't inline any functions from the template.  GHC has a nasty habit
-- of deciding to inline happyGoto everywhere, which increases the size of
-- the generated parser quite a bit.

{-# LINE 312 "templates/GenericTemplate.hs" #-}
{-# NOINLINE happyShift #-}
{-# NOINLINE happySpecReduce_0 #-}
{-# NOINLINE happySpecReduce_1 #-}
{-# NOINLINE happySpecReduce_2 #-}
{-# NOINLINE happySpecReduce_3 #-}
{-# NOINLINE happyReduce #-}
{-# NOINLINE happyMonadReduce #-}
{-# NOINLINE happyGoto #-}
{-# NOINLINE happyFail #-}

-- end of Happy Template.
