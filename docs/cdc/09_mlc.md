Architecture envisagée
======================

Note préalable
--------------

Bien que nous ayons mûrement réfléchi sur l'architecture que nous allions
mettre en place nous ne pouvons garrantir que le projet final sera implémenté
tel que nous l'envisageons actuellement : de nouvelles idées peuvent émerger et
les benchmark vont très probablement nous permettre d'obtenir énormément
d'informations nous permettant de faire évoluer notre système.

Architecture système du cluster
-------------------------------

Nous avons décidé de réaliser un système de parallélisation de tâche destiné à
fonctionner en réseau, sur plusieurs machines. Celui-ci sera basé sur deux
types de machines : le dispatcher (ou le maître), chargé de séquencer et
d'organiser les différentes étapes de calcul et les noeuds (ou les esclaves)
qui effectuent des tâches.

![Un technicien de My Little Cluster en train de maintenir l'arcihtecture](images/cluster.jpg)

### Les noeuds de calcul

Les noeuds seront chargés d'effectuer les tâches envoyées par le dispatcher,
puis de faire remonter le résultat associé à chaque tâche.


#### Contraintes

  * Les disques durs étant coûteux et les temps d'accès long, le système d'exploitation doit pouvoir être chargé entièrement en RAM et fonctionner sans disque dur.
  * Le dispatcher doit avoir possibilité de contrôler l'ensemble des noeuds facilement (reboot, vérification de l'état, ...)
  * Le kernel doit permettre de multi-threader les processus pour tirer profit
    des processeurs multi-coeurs
  * La stabilité du noeud importe peu, en cas d'erreur ou de crash du kernel le
    protocole sera capable de remettre le noeud en fonctionnement

Pour ces raisons nous nous orienterons probablement sur une distribution
linux sur mesure minimaliste comprenant le kernel et le strict minimum (libc,
un shell et quelques binaires tout au plus).

### Le dispatcher

Le dispatcher a pour rôle d'organiser les tâches nécessaire au calcul. Il va
donc répartir le travail entre chaqun des noeuds et récupérer les différents
résultats.

L'architecture système du dispatcher est beaucoup moins stricte que celle des
noeuds de calcul : il n'est pas en soit un goulot d'étranglement pour la
vitesse de calcul et il n'y en a qu'un seul par cluster.

Nous développerons donc un dispatcher fonctionnant sur LInux. Il offrira la
possibilité de sauvegarder les tâches déja calculées pour reprendre le calcul
en cas d'interruption.
