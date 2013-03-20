{

module Parser where

import Data.Char
import Prelude
import Ast
import Lexer

}

%name parse
%tokentype { Located TokenType }
%error { parseError }
%monad { Parser } { thenP } { returnP }
%lexer { lexer } { L _ TokEOF }

%token
    "let"                            { L _ TokLet }
    "in"                             { L _ TokIn }
    "="                              { L _ TokEq }
    "+"                              { L _ TokPlus }
    "-"                              { L _ TokMinus }
    "*"                              { L _ TokMul }
    "/"                              { L _ TokDiv }
    "("                              { L _ TokOPar }
    ")"                              { L _ TokCPar }
    ","                              { L _ TokComma }
    "<"                              { L _ TokLess }
    ">"                              { L _ TokMoar }
    "<="                             { L _ TokLeq }
    ">="                             { L _ TokMeq }
    var                              { L _ (TokVar $$) }
    int                              { L _ (TokNbr $$) }
    "if"                             { L _ TokIf }
    "then"                           { L _ TokThen }
    "else"                           { L _ TokElse }
    "end"                            { L _ TokEnd }
    "["                              { L _ TokOBrack }
    "]"                              { L _ TokCBrack }
    ";"                              { L _ TokSemiColon }

%left "="
%left "else"
%left "<" "<=" ">" ">="
%left "+" "-"
%left "*" "/"

%%

Program : Decs                       { $1 }

Decs : Decs Dec                      { $2:$1 }
     |                               { [] }

Dec : Ids "=" Exp                    { ($1, $3) }

Ids : var Ids                        { $1:$2 }
    |                                { [] }

Exp : var                            { Var $1 }
    | Exp "+" Exp                    { Add $1 $3 }
    | Exp "-" Exp                    { Sub $1 $3 }
    | Exp "/" Exp                    { Div $1 $3 }
    | Exp "*" Exp                    { Mul $1 $3 }
    | Exp "<" Exp                    { Less $1 $3 }
    | Exp ">" Exp                    { Great $1 $3 }
    | Exp "<=" Exp                   { Leq $1 $3 }
    | Exp ">=" Exp                   { Geq $1 $3 }
    | "(" Exp ")"                    { Paren $2 }
    | "if" Exp "then" Exp "else" Exp { If $2 $4 $6}
    | ListLit                        { ListLit $1 }
    | "let" Decs "in" Exp "end"      { Let $2 $4}
    | int                            { Nbr $1 }


ListLit : "[" ListParam "]"          { $2 }

ListParam : Exp "," ListParam        { $1:$3 }
          | Exp                      { [$1] }

{

parseError :: Located TokenType -> Parser a
parseError tok (s, l, c) = fail $ "parse error at `" ++ show (take 10 s)
    ++ "' line " ++ show l ++ " on token: " ++ show tok

}

