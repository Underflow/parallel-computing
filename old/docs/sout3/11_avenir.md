<fontsize>$12$</fontsize>

Pour la seconde soutenance
---------------------------

### Différentes applications :

Pour la prochaine soutenance, nous prévoyons de donner une réelle
application à notre travail. 
Tout d'abord, nous souhaitons travailler sur différentes applications
parallélisables.

1. Un Bruteforce :
Nous allons implémenter un processus qui permettra de découper les tâches
d'un bruteforce. Pour calculer un mot de passe de 10 caractères
alphabétiques/numériques, on transmettra une plage de test à chacun des
postes, on augmentera alors significativement la vitesse de calcul de celui-ci.

2. Affichage d'un certain nombre de décimales du nombre pi :
On pourra afficher un certain nombre de décimales de pi plus rapidement qu'un
ordinateur seul en utilisant un principe mathématique.

3. Calcul graphique
On peut significativement augmenter les capacités graphiques d'un ordinateur en
répartissant les tâches de calcul graphique sur différents postes.


La parallélisation offre énormement de possibilités d'applications et nous
réfléchirons sur d'autres applications que celles listées ci-dessus à l'avenir.

### Une amélioration de l'interface :

Enfin nous nous tournerons sur une amélioration significative de notre
interface. Celle-ci nous permettra par exemple de visualiser en temps réel les 
postes en ligne et donc disponibles pour nos applications. On pourra également
aisément transmettre par ligne de commandes des actions à distribuer par le
serveur. On pourra par exemple à partir de cette ligne de commande :

- Demander un Hello World général
- Lancer une application de calcul
- Allumer/Eteindre des postes

\newpage

### Nouveau moteur

Guillaume s'étant récemment passionné pour les machines virtuelles et adorant
la théorie des langages (Tiger et LRDE obligent), il s'est mis en tête de nous
fournir une couche d'abastraction légère, une VM aux primitives conçues
spécifiquement pour du calcul distribué, dans un langage qui ressemblerait à un
subset de Haskell. Ayant décroché son stage d'ing2 dans l'équipe HHVM chez
Facebook, il souhaite vraiment acquérir une réelle compétences dans les
domaines du langages et de la compilation pour s'y préparer au mieux.

#### Machine Virtuelle Distribuée (DVM)

La DVM sera Métaprogrammée selon les designs exprimés sur le blog technique de
Guillaume (http://Vermeille.fr/ article Metaprogramming a full Virtual
Machine). Cette approche permet l'aisance et la beauté du code, tout autant que
la performance. Elle est conceptuellement très liée au langage,
puisqu'exploitant la force de ses concepts.

Cette VM est orientée pile, avec des simulations de registres d'arguments et de
registres locaux (comme on peut en retrouver dans les SPARCs) pour faciliter
l'écriture du code assembleur, tant pour les humains que le compilateur futur.
Le seul intérêt des registres étant le temps d'accès, ce n'est une architecture
pertinente que dans le cas des machines physiques. On se libère donc de cette
contrainte.

Les opérations de base qu'on y trouvera seront donc

    Gestion de la pile

    PUSH
    POP

    Accès mémoires

    LD
    ST

    Opérations arithmétiques

    ADD
    SUB
    MUL
    DIV

    Accès distribués

    SEND
    ACCESS

Ces quelques primitives devraient déjà occuper les 256 opcodes possibles. A
termes, nous aimerions que cette machine virtuelle implémente une notion de JIT
compilation.

#### Langage de script (DHas)

DHas, pour Distributed Haskell, sera notre langage d'écriture des programmes
distribués. Subset de ce vermeilleux langage de programmation, il en tirera
tous les bénéfices :

- Fonctionnel pur
- Lazy

La pureté du langage lui permet d'être trivialement parallélisable : en effet,
si aucune fonction n'effectue d'effet de bord, ni en lecture ni en écriture, et
que le retour d'une fonction ne dépend de rien d'autre que de ses arguments,
alors on n'a pas besoin de conserver de contexte, et on peut déporter le calcul
sur une autre machine, simplement en indiquant la fonction à exécuter en point
d'entrée, et ses arguments. On récupère la valeur de retour, on la remet de
façon transparente dans notre exécution, et tout s'est déroulé comme si le
calcul avait eu lieu en local. Aucune problématique d'accès concurrent n'est
présente : pas de mutexes, de sémaphores, etc.

La laziness est une méthode d'évalution. Contrairement au C qui est un langage
d'évaluation stricte, Haskell évalue ses valeurs seulement quand c'est
nécessaire. Le langagene calcule pas immédiatement, mais retient comment le
calcul doit être effectué, c'est ce qui lui permet d'implémenter des listes
infinies. Tant que l'item 1000000 n'est pas nécessaire au calcul, il ne sera
pas calculé. La pertinence de la laziness dans DHas est encore sujet à débat,
et son implémentation est sans doute ardue.

Le compilateur DHas sera donc implémenté en Haskell et produira du bytecode
pour la DVM. Le lexer est développé par nos soins, le parseur est réalisé avec
Happy, générateur de parseurs LALR pour Haskell (imitation de bison)

Enfin, le système de typage reste à décider, une inférence de type à base de
TypeClasses comme Haskell n'est certainement pas accessible dans les délais
impartis.

La grammaire est encore très approximative :

    Program : Decs

    Decs : Decs Dec
         | {- empty -}

    Dec : Ids "=" Exp

    Ids : "var" Ids
        | {- empty -}

    Exp : var
        | Exp "+" Exp
        | Exp "-" Exp
        | Exp "/" Exp
        | Exp "*" Exp
        | Exp "<" Exp
        | Exp ">" Exp
        | Exp "<=" Exp
        | Exp ">=" Exp
        | "(" Exp ")"
        | "if" Exp "then" Exp "else" Exp
        | ListLit
        | "let" Decs "in" Exp "end"
        | int


    ListLit : "[" ListParam "]"

    ListParam : Exp "," ListParam
              | Exp

Le système reposera sur la notion de future : pouvoir commencer un calcul qui
n'est pas bloquant en tâche de fond, continuer, et ne bloquer que quand le
résultat est réellement nécessaire. Idéalement, l'opérateur de future serait @

Voici un exemple de code DHas :

    function1 a b =
        let var1 = @distribfun a
            tmp = fun2 4 a
            tmp2 = fun3 b 666
        in
            fun4 (b + a) var1
        end

Ainsi, le calcul de `distribfun a` est confié à une autre machine du cluster au
début, les appels à fun2 et fun3 sont exécutés en local, puis, on récupère la
valeur de la future de `var1`, en évaluation bloquante.

