<fontsize>$12$</fontsize>

Première soutenance
==================================
Répartitions des tâches (scheduling)
------------------------------------
En ce qui concerne la répartition des tâches, nous avons choisi de fonctionner avec une liste circulaire.
Cette liste circulaire a une taille fixée de n tâches. On attribue toute tâche encore dans la liste à un noeud de notre cluster, soit à un client. 
Une fois que la tâche est achevée par le noeud, celle-ci est retirée de la liste et est remplacée par une nouvelle tâche si il en reste à faire.

* * *
Le but de ce type de liste circulaire est le suivant : admettons que nous ayons 2000 tâches à répartir, il serait inutile de faire une liste d'une taille de 2000 tâches car la liste serait beaucoup trop grande. Ainsi, avec notre principe de liste circulaire à taille fixée, on créera une liste de 100 tâches, par exemple, que l'on remplira avec 100 tâches des 2000 à effectuer. Dès qu'une tâche de la liste est terminée, on la remplace par une tâche parmi les 1900 autres restantes et ainsi de suite jusqu'à avoir effectuer la totalité des tâches.

* * *

Chaque tâche de la liste possède deux champs:

- un "id", qui est un entier qui représente le numéro de la tâche parmi la totalité des tâches à faire (2000 dans l'exemple précédent) et non pas parmi les n tâches à faire avec n la taille de la liste circulaire.

- un champ "task", qui est une chaîne de caractères, qui contiendra une commande qui lancera un éxécutable permettant d'effectuer la tâche (un calcul par exemple).

* * *

Notre principe est comparable à un algorithme d'ordonnancement, appelé "Round-Robin". Un algorithme d'ordonnancement (scheduling) permet de choisir parmi un ensemble de tâches prêtes celle qui va occuper un serveur. Cet algorithme peut ou non utiliser des priorités affectées aux tâches.

Avec un algorithme sans interruption, la tâche élue conserve le client jusqu'à sa terminaison : elle ne peut être interrompue ni par l'arrivée d'une autre tâche, ni par une interruption horloge. Avec un algorithme avec réquisition et sans recyclage, seule l'arrivée d'une tâche plus prioritaire peut interrompre la tâche élue. La tâche élue est alors remise en tête de la file des tâches prêtes.

Pour la première soutenance, nous n'avons pas encore défini de priorité parmi les tâches parce que nous n'avons pas encore d'applications.
