\newpage
Une application : Mario !
-------------------------

Pour tester notre cluster, notre premier test consiste à jouer une musique
définie en terme de fréquence, de durée de note et d'intervalle sur plusieurs
machines à l'aide de leur buzzer.


Nos noeuds pouvant directement executer des commandes shell, nous avons utilisé
la commande echo pour faire bipper les différentes machines.


L'execution des différentes tâches doit être synchronisé de façon à ce que les
différentes machines ne jouent pas toutes en même temps et de façon rythmée.
C'est globalement ce qui nous a causé le plus de problèmes mais cela nous a
permis de mieux appréhender les fonctions que devra pouvoir permettre le
scheduler.
