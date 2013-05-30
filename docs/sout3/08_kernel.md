\newpage

Soutenance 1
===================

Noyau d'exploitation des machines
---------------------------------

Afin de faire fonctionner les différentes tâches sur le PIE nous avons eu
besoin de réaliser une distribution linux minimaliste, embarquant un kernel à
jour et busybox. Ce noyau peut-être amorcé sans disque dur lorsqu'il est booté 
avec PXE par exemple. Dans ce cas, le disque dur est simulé par la RAM.


Le noyau peut etre amorcé via un boot PXE. Nous avons réalisé un script
d'initialisation qui ne lance non pas un shell mais le binaire /cluster/init.


Ce binaire va se charger de demander des tâches en boucle au dispatcher, puis
de les executer. Les tâches sont des commandes shell que le programme va
executer. La sortie standart de ces commandes constitue le résultat de la tâche
qui sera retourné au dispatcher.


Les tâches peuvent donc dors et déjà être placées dans des binaires dans
l'archive du noyau et la tache envoyée sur le réseau ne sera qu'une simple
commande d'appel de ces binaires.


Pour faciliter la manipulation du noyau nous avons réalisé des scripts
permettant de recompiler automatiquement nos binaires-tâches, de décompresser
le noyau, d'inclure les binaires et de reformer l'archive. Ceci nous permet de
redéployer un nouveau noyau pour notre cluster en deux commandes ce qui est
très pratique !
