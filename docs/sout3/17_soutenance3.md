\newpage{}

# Soutenance 3

## Un algorithme génétique de dessin

Nous avons conçu un algorithme génétique de reproduction d'images que nous
réalisé en C. L'objectif de cet algorithme est de reproduire une image, en
utilisant uniquement des carrés de tailles et de couleurs différentes en se
servant d'un algorithme génétique. 

### Un algorithme génétique

Un algorithme génétique sur la théorie de l'évolution de Darwin pour résoudre
un problème. Il fonctionne donc sur le même principe fondamental que la
sélection naturelle des êtres vivants : "l'individu le plus adapté aura plus de
chance de se reproduire".

Tous les algorithmes génétiques fonctionnent selon le même principe:

1. On génère une population d'individus avec un ADN aléatoire

2. On classe les individus selon leur aptitude à résoudre un problème donné

3. On génère une nouvelle génération d'individus en effectuant les croisements
entre les individus de la dernière génération. Les individus les mieux classés
ont une probabilité plus forte d'engendrer une progéniture.

4. On effectue des mutations aléatoires sur les individus (avec une
   probabilité relativement faible pour ne pas reproduire de générations de
   dégénérés)

5. Retour à l'étape 2.

Pour implémenter un algorithme génétique, il faut d’abord définir le sens de l’ADN des individus. C’est à dire à quoi correspondront les données contenu dans l’ADN. Pour faire le parallèle avec les êtres vivants, dans un organisme l’ADN est transcrit en ARN qui est ensuite traduit en protéine.
De la même façon il faut réaliser une fonction de « traduction ». Dans mon cas, la fonction de traduction transforme l’ADN en une image. L’ADN contient en fait les coordonnées des carrés et leur couleur.

Ensuite, il est nécessaire de déterminer une fonction déterminant le fitness des individus, c’est à dire un score d’adaptation au problème à résoudre. J’ai choisi pour ce projet d’utiliser une bête fonction de comparaison d’image. Elle retourne la somme de la différence des couleurs de chaque pixels entre l’image source et celle de l’individu.

Enfin il faut une fonction de croisement (aka crossover) qui mélangera deux ADN pour brasser les générations. Sur mon programme, le croisement s’effectue gène par gène (ou carré par carré si vous préférez) et non pas octet par octet ce qui n’aurait eu aucun sens (ou toute autre méthode de croisement adaptée à d’autres algorithmes génétiques).

Une fois que tout ceci est correctement codé, la magie opère toute seule, et un dessin « correct » arrive très vite à l’écran !

### Evolution d'une population :

Voici une sortie console dans laquelle est affiché un score. Ce score correspond au pourcentage de ressemblance entre l'image génétique et l'image à reproduire.

Generation : 0 - Best fitness : 69.230701
\newline
Generation : 10 - Best fitness : 72.895536
\newline
Generation : 20 - Best fitness : 74.464792
\newline
Generation : 30 - Best fitness : 75.163049
\newline
Generation : 40 - Best fitness : 76.264078
\newline
Generation : 50 - Best fitness : 76.895984
\newline
Generation : 60 - Best fitness : 77.855822
\newline
Generation : 70 - Best fitness : 78.508686
\newline
Generation : 80 - Best fitness : 79.311399
\newline
Generation : 90 - Best fitness : 79.834519
\newline
Generation : 100 - Best fitness : 80.285271
\newline
Generation : 110 - Best fitness : 80.652855
\newline
Generation : 120 - Best fitness : 81.155114
\newline
Generation : 130 - Best fitness : 81.250519
\newline
Generation : 140 - Best fitness : 81.679887
\newline
Generation : 150 - Best fitness : 81.935676
\newline
Generation : 160 - Best fitness : 82.397639
\newline
Generation : 170 - Best fitness : 82.737401
\newline
Generation : 180 - Best fitness : 83.023686
\newline
Generation : 190 - Best fitness : 83.427936
\newline
Generation : 200 - Best fitness : 83.569475
\newline
Generation : 210 - Best fitness : 83.896074
\newline
Generation : 220 - Best fitness : 84.156327
\newline
Generation : 230 - Best fitness : 84.421856
\newline
Generation : 240 - Best fitness : 84.653619
\newline
...
\newline
Generation : 280 - Bestfitness : 85.210001
\newline
...
\newline
Generation : 460 - Bestfitness : 87.734134
\newline
...
\newline
Generation : 910 - Bestfitness : 90.093073
\newline
...
\newline
Generation : 1810 - Bestfitness : 91.600760
\newline

### Version distribué de l'algorithme génétique :


Pour permettre à notre algorithme génétique de distribuer les tâches aux
différents clients, on procède en plusieurs étapes :

1. Le serveur va distribuer des populations aléatoires à chaque client.
\newline
2. Chacun des clients va faire évoluer sa population grâce à un algorithme
   génétique.
\newline
3. Au final chacun des clients a fait évoluer le génome (code génétique des  
   individus) contenu dans les populations. Celle ci est alors retournée au
   serveur.
\newline
4. Le serveur mixte les différentes populations reçues par chacun des clients.
   Si on compare les populations générées par les clients à des continents, on
   se rend compte que les continents possèderont une population plus
   diversifiée évitant ainsi de tomber dans des minimums locaux.
\newline




Voici typiquement le rendu obtenu au bout de quelques minutes de calculs :
\newline
\hspace*{0mm}\vfill
\begin{center}
\includegraphics{images/mario.png}
\newline
Et voici un exemple un peu plus évolué :
\newline
\includegraphics{images/genetik1.png}
\end{center}
\vfill\hspace*{0mm}
