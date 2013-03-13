<fontsize>$12$</fontsize>

Interface utilisateur
---------------------

L'interface utilisateur que nous proposons est réalisée avec les bibliothèques
ncurses (New Curses) et CDK (Curses Development Kit). Tout s'affiche dans un
terminal, et est contrôlable entièrement avec le clavier.

Elle se compose de trois onglets, respectivement un terminal qui permettra de
commander les tâches à effectuer ainsi que les noeuds en charge de celles-ci,
un aperçu des noeuds connectés sous forme de cartographie des salles du parc
informatique, et une page "à propos" et d'aide pour l'utilisation du terminal
et de l'aperçu des noeuds connectés.

Concernant le terminal (premier onglet), il y aura deux panneaux disponibles
avec d'un côté un shell pour entrer des commandes de gestion des noeuds ou pour
lancer l'éxécution d'un programme, et de l'autre les logs tels que les
déconnexions/timeouts des noeuds, les nouvelles connexions, l'envoi des tâches
et la réception des résultats.

Le deuxième onglet nous affiche actuellement la cartographie d'une salle en
fonction de la rangée et du numéro de poste de chaque noeud connecté ou
anciennement connecté (dans ce cas ils apparaissent comme déconnectés). Ceux
qui sont en ligne sont affichés en vert, et les autres en rouge pour une
compréhension visuelle rapide. Nous allons ajouter un paramètre à chaque noeud
afin de renseigner également la salle dans laquelle il est, ainsi que des
sous-onglets pour se déplacer entre les salles.

Finalement, le dernier onglet affichera le manuel du programme ainsi que
quelques informations sur le projet, et des crédits.
