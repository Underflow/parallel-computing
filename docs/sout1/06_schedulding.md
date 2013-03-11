Répartition des tâches
=========================

En ce qui concerne la répartition des tâches, nous avons choisi de fonctionner avec une liste circulaire.
Cette liste circulaire a une taille fixée de n tâches. On attribue toute tâche encore dans la liste à un noeud de notre cluster, soit à un client. 
Une fois que la tâche est achevée par le noeud, celle-ci est retirée de la liste et est remplacée par une nouvelle tâche si il en reste à faire.
Le but de ce type de liste circulaire est le suivant : admettons que nous ayons 2000 tâches à répartir, il serait inutile de faire une liste d'une taille de 2000 tâches car la liste serait beaucoup trop grande. Ainsi, avec notre principe de liste circulaire à taille fixée, on créera une liste de 100 tâches, par exemple, que l'on remplira avec 100 tâches des 2000 à effectuer. Dès qu'une tâche de la liste est terminée, on la remplace par une tâche parmi les 1900 autres restantes et ainsi de suite jusqu'à avoir effectuer la totalité des tâches.
Chaque tâche de la liste possède deux champs: 
- un "id", qui est un entier qui représente le numéro de la tâche parmi la totalité des tâches à faire (2000 dans l'exemple précédent) et non pas parmi les n tâches à faire avec n la taille de la liste circulaire.
- un champ "task", qui est une chaîne de caractères, qui contiendra une commande qui lancera un éxécutable permettant d'effectuer la tâche (un calcul par exemple).