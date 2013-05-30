\newpage

Soutenance 1
===================

Pour la première soutenance, nous avons établi une structure à notre projet.

Rappelons quelques points importants de la première soutenance.

###  Noyau d'exploitation des machines

Chaque client fonctionne grâce à l'embarquement d'une distribution linux
minimaliste. Le noyau est amorcé grâce à un boot PXE. 
Une fois le noyau déployé sur un client, un script d'initialisation va
se charger de demander en boucle des tâches au serveur.

###  Schedulding

La répartition des tâches s'effectue grâce à une liste circulaire gérée par le
serveur. Chaque tâche de la liste possède les champs suivant : "id" et "task".
L'identifiant est le numéro de la tâche dans la liste. Le champ task contient
la tâche à effectuer sous forme d'une commande shell.

###  Premières applications à notre projet

Nous avons implémenter deux applications pour cette première soutenance. L'une
d'elles présentait un aspect "fun" tandis que l'autre effectuait les premiers
calculs. Ces deux applications représentait les bases du projet.

#### Application MARIO :

Pour cette application, le serveur découpait la musique de mario et génerait
dans la liste circulaire différentes tâches pour les clients. Grâce à
différentes fréquences et à des calculs d'intervalles de temps, nous avons fait
jouer par N clients connectés au serveur, la musique de MARIO en faisant bipper
les machines.

#### Application BRUTEFORCE : 

Pour faire fonctionner le BRUTEFORCE, le serveur découpait des plages de
1.000.000 de tests et les distribuait au fur et à mesure aux différents
clients. 

###Noyau d'exploitation des machines


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
