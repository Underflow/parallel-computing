Calcul distribué en réseau
--------------------------

En anglais, le terme "cluster" signifie "grappe". "Computer cluster" désigne donc un regroupement de plusieurs ordinateurs indépendants.

Chaque ordinateur sera appelé de "noeud" et sera utilisé comme un serveur de calcul indépendant. Mais le cluster final sera considérée comme une seule et même entité.

Les objectifs d'une telle configuration sont multiples : dépasser les limitations d'un seul ordinateur, augmenter la disponibilité... En bref, le "computer cluster" sert à obtenir de plus grandes performances.

En effet, la principale utilisation du "computer cluster" est le calcul parallèle.

### Comment regrouper la puissance de plusieurs ordinateurs ?

Le procédé est très simple : on relie les ordinateurs via le réseau, en général un réseau local rapide puis on donne du travail à chaque noeud de façon intelligente de façon à respecter les contraintes entrainées par une architecture parralèle pour faire progresser le calcul.

Nous présenterons dans la section suivante l'architecture que nous avons pensé
pour notre cluster.
