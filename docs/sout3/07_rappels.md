# Rappels du projet MyLittleCluster

## Le principe du projet

Notre projet MyLittleCluster est un projet de parallélisation. Paralléliser un algorithme permet de distribuer les tâches entre
plusieurs noeuds de calcul et ainsi diviser le temps nécessaire à sa réalisation.

Par exemple, un algorithme permettant de retrouver un mot de passe à base
de sa signature nécessite de tester une à une toutes les combinaisons possibles
jusqu’à trouver le hash recherché. Si la fonction de hashage est sûre, il n’existe
pas de méthode de recherche plus optimisée. L’intérêt de diviser le calcul si l’on
dispose de plusieurs machines pour effectuer un tel calcul est alors évident.

Nous avons décidé de réaliser un système de parallélisation de tâche destiné à
fonctionner en réseau, sur plusieurs machines. Celui-ci sera basé sur deux types
de machines : le dispatcher (ou le maître), chargé de séquencer et d’organiser
les différentes étapes de calcul et les noeuds (ou les esclaves) qui effectuent des
tâches.


## Première soutenance

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


