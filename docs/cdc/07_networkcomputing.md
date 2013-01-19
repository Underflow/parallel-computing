Calcul distribué en réseau
==========================

Computer cluster
----------------

Ce terme va jouer un grand rôle dans notre projet, c'est pourquoi nous allons définir maintenant ce qu'on nous désignons par celui-ci. 

En anglais, le terme "cluster" signifie "grappe". "Computer cluster" désigne donc un regroupement de plusieurs ordinateurs indépendants. Chaque ordinateur sera qualifié de "noeud" et sera utilisé comme un serveur indépendant. Mais la "grappe" finale sera considérée comme une seule et même entité.
Les buts d'une telle configuration sont multiples : dépasser les limitations d'un seul ordinateur, augmenter la disponibilité... En bref, le "computer cluster" sert à obtenir de plus grandes performances.
En effet, la principale utilisation du "computer cluster" est le calcul parallèle.
Comment regrouper plusieurs ordinateurs entre eux ?
Le procédé est très simple : on relie les ordinateurs via le réseau, en général un réseau local rapide.

Dans notre cas, par exemple si nous voulions "cracker" un mot de passe, chaque noeud/ordinateur effectuera une tâche, par exemple ici, un noeud aura pour tâche d'essayer des combinaisons de mots de passe sur une certaine plage, et un autre s'occupera en même temps d'une autre plage.
