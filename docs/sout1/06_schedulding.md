R�partition des t�ches
=========================

En ce qui concerne la r�partition des t�ches, nous avons choisi de fonctionner avec une liste circulaire.
Cette liste circulaire a une taille fix�e de n t�ches. On attribue toute t�che encore dans la liste � un noeud de notre cluster, soit � un client. 
Une fois que la t�che est achev�e par le noeud, celle-ci est retir�e de la liste et est remplac�e par une nouvelle t�che si il en reste � faire.
Le but de ce type de liste circulaire est le suivant : admettons que nous ayons 2000 t�ches � r�partir, il serait inutile de faire une liste d'une taille de 2000 t�ches car la liste serait beaucoup trop grande. Ainsi, avec notre principe de liste circulaire � taille fix�e, on cr�era une liste de 100 t�ches, par exemple, que l'on remplira avec 100 t�ches des 2000 � effectuer. D�s qu'une t�che de la liste est termin�e, on la remplace par une t�che parmi les 1900 autres restantes et ainsi de suite jusqu'� avoir effectuer la totalit� des t�ches.
Chaque t�che de la liste poss�de deux champs: 
- un "id", qui est un entier qui repr�sente le num�ro de la t�che parmi la totalit� des t�ches � faire (2000 dans l'exemple pr�c�dent) et non pas parmi les n t�ches � faire avec n la taille de la liste circulaire.
- un champ "task", qui est une cha�ne de caract�res, qui contiendra une commande qui lancera un �x�cutable permettant d'effectuer la t�che (un calcul par exemple).