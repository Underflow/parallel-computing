\newpage{}

## Compilateur

Afin de simplifier le développement des applications exécutées en parallèle sur
le cluster, nous avons eu l'idée de proposer un langage spécialement fait pour
ne pas se soucier de toute la problématique engendrée par le développement avec
séparation des taches, ou leur envoi et leur réception.

Le compilateur que nous possédons est à ce jour capable de parser puis compiler
du code "lanus" directement en C, puis de compiler ce qui est généré.

De nouveaux opérateurs ont été ajoutés comme par exemple le "@" devant l'appel
d'une fonction qui sert à la séparer en une liste d'exécutions simultanées qui
sont ensuite dispatchées et envoyées aux noeuds disponibles. Il est évident que
la syntaxe est réellement plus lisible, et cela permet egalement d'éviter des
erreurs communes comme la multiple exécution d'une meme tache, ou de perdre des
données lorsque qu'un noeud ayant reçu une tache ne répond plus.

Il est également à noter que ce langage ne comporte pas de pointeurs, et cela
permet de supprimer l'effet de bord causé lors de l'exécution des fonctions.
C'est un pas de plus vers la simplicité du code, car on n'a pas à se soucier de
la mémoire des noeuds.

### Lexer

La première étape du développement du compilateur, a été de faire un "lexer".
Il s'agit d'un sous-programme chargé de détecter la grammaire d'une chaine de
caractères contenant du code.

Les différents mots-clés de la grammaire utilisée comporte :

- Identifiants : `type "id" [ "=" exp ] ";";`
- Entiers, flottants :
    type: "int" | "float"; \\
    num: float | int | bool; \\
- Opérateurs arithmétiques et comparaison :
    affect: ["id" "="] logic; \\
    logic: comp { ("or" | "and") low_exp } \\
    comp: low_exp { ("<" | "==" | ">" | ">=" | "<=") low_exp } \\
    low_exp: high_exp { ("+"|"-") high_exp }; \\
    high_exp: pren { ("/" | "*" | "%") paren }; \\
- Mots clés du langage :
    term: "id" \\
        | "num" \\
        | funcall; \\
- Paranthèses, accolades : `proto: type "id" "(" {"type" "id" ","} ")";`
- Conditions :
    comp_exp: instr; \\
        | "if" "(" exp ")" block [ "else" block ]; \\
        | "while" "(" exp ")" block; \\

### Parseur

Le parseur est le sous-programme qui se charge de reconnaitre la grammaire de
notre langage. Pour simplifier sa création, nous avons ecrit une grammaire de
type LL1.

Nous avons choisi de réaliser un lexer et un parseur à la main, pour
s'entrainer à écrire de tels programmes et grace à cela, utiliser un
compilateur de compilateur tel `aue`, `lex` et `yacc`.
