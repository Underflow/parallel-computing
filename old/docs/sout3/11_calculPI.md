## Calcul de PI


Nous disposons désormais d'une nouvelle application permettant de calculer un
nombre élevé de décimales de PI. Le calcul étant infiniment long, nous avons
décidé de paraléliser le calcul de sorte à accélerer la géneration des
décimales de PI.

Pour se faire nous nous sommes basés sur des formules mathématiques indiquant
qu'il était possible de découper en plusieurs tâches ce calcul.

L'intégrale suivante vaut pi:


$$f(x) = \frac{4}{1+x^2}$$


$$\begin{array}{rcl}
\int_0^1 f(x)dx & = & 4\int_0^1 \frac{1}{1+x^2}dx  \\
& = & ([\arctan(x)]_0^1) \\
& = & 4(arctan(1)-arctan(0)) \\
& = & 4(\frac{\pi}{4} - 0) \\
\end{array}$$



Nous alons exprimer cette intégrale grâce à un découpage en trapèzes. En effet,
on a dans un cas géneral :


$$\displaystyle  \int_a^b f(x)dx = \lim_{n\to \infty} \sum_{i=1}^n (f(x_i) + f(x_i + 1)) \frac{h}{2}$$

avec : 

$$\displaystyle  h =  \frac{b-a}{n}$$

et :

$$\displaystyle  x_i =   (i - 1)h + a$$

L'approximation (nécessaire vu qu'on ne peut pas calculer numériquement une
somme infinie sur une machine !) consistera à utiliser un n fini, et non plus
le faire tendre vers l'infini. Plus n sera grand, plus l'approximation sera
bonne :

$$\displaystyle  \int_a^b f(x)dx \approx \sum_{i=1}^n (f(x_i) + f(x_i + 1))
\frac{h}{2}$$


En appliquant cette formule à notre cas particulier, on obtient :

$$\int_0^1 f(x)dx \approx \frac{1}{2} \sum_{i=1}^n (f(\frac{i-1}{n}) +
f(\frac{i}{n})$$


Notre programme va donc calculer cette somme finie pour un n grand, ce qui nous
donnera comme résultat une (bonne) approximation de pi.


Chaque tâches génerées par le serveur aura donc pour objectif de calculer des sommes.
On fixera les sommes par "pas". Par exemple pour un pas de 2500 :

$$\sum_{i=1}^{2500} ...$$



![Pi](./images/retouche_pi.png)
