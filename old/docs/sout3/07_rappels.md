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



