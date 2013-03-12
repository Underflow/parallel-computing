Interface utilisateur
---------------------

L'interface utilisateur que nous proposons est realisee avec les bibliotheques
ncurses (New Curses) et CDK (Curses Development Kit). Tout s'affiche dans un
terminal, et est controlable entierement avec le clavier.

Elle se compose de trois onglets, respectivement un terminal qui permettra de
commander les taches a effectuer ainsi que les noeuds en charge de celles-ci,
un apercu des noeuds connectes sous forme de cartographie des salles du parc
informatique, et une page "a propos" et d'aide pour l'utilisation du terminal
et de l'apercu des noeuds connectes.

Concernant le terminal (premier onglet), il y aura deux panneaux disponibles
avec d'un cote un shell pour entrer des commandes de gestion des noeuds ou pour
lancer l'execution d'un programme, et de l'autre les logs tels que les
deconnexions/timeouts des noeuds, les nouvelles connexions, l'envoi des taches
et la reception des resultats.

Le deuxieme onglet nous affiche actuellement la cartographie d'une salle en
fonction de la rangee et du numero de poste de chaque noeud connecte ou
anciennement connecte (dans ce cas ils apparaissent comme deconnectes). Ceux
qui sont en ligne sont affiches en vert, et les autres en rouge pour une
comprehension visuelle rapide. Nous allons ajouter un parametre a chaque noeud
afin de renseigner egalement la salle dans laquelle il est, ainsi que des
sous-onglets pour se deplacer entre les salles.

Finalement, le dernier onglet affichera le manuel du programme ainsi que
quelques informations sur le projet, et des credits.
