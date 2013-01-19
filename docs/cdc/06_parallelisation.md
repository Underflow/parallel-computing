La parallélisation
==================

Pourquoi paralléliser un calcul ?
---------------------------------

Certains algorithmes peuvent demander des temps de calcul importants ou très
important. Paralléliser un algorithme permet de distribuer les tâches entre
plusieurs noeuds de calcul et ainsi diviser le temps nécessaire à sa
réalisation.

Par exemple, un algorithme permettant de retrouver un mot de passe à base de sa
signature nécessite de tester une à une toutes les combinaisons possibles
jusqu'à trouver le hash recherché. Si la fonction de hashage est sûre, il
n'existe pas de méthode de recherche plus optimisée. L'intérêt de diviser le calcul si l'on dispose de plusieurs machines pour effectuer un tel calcul est alors évident.

Les contraintes de la parrallélisation
--------------------------------------

Pour faire fonctionner un programme sur plusieurs clusters de calcul
travaillant en collaboration on doit avoir pensé le programme pour un tel mode de fonctionnement.

### Les effets de bords

Les algorithmes itératifs non designés pour fonctionner sur des architectures
parallélisées contiennent des effets de bord, c'est à dire que l'opération
d'une instruction executée à un instant t dépend des instructions éxecutées
précédemment.

Ainsi, si nous possédons plusieurs noeuds de calcul et que nous décidions d'envoyer à chaque noeud une instruction différente aucun parallélisme ne serait possible car chaque noeud devrait attendre que les noeuds en charge des instructions précédentes aient fini d'executer leurs instructions. Cela revient strictement à une éxecution séquentielle des instructions.

La première difficulté est donc de minimiser les effets de bords pour minimiser
les temps d'attente pour executer les instructions.

### Les problématiques d'accès mémoire

Si tous les noeuds travaillent sur le même espace mémoire, il peut se produire
des problèmes d'accès si deux tâches tentent d'accéder au même emplacement.
