# wave-propagation


Voici le repository pour travailler sur le projet des la propagation d'onde en 3D avec comme collaborateur Tommaso et Guy-Raphaël.


Explications concernant les sources continues et les points réfléchissant (par Guy-Raphaël) :
voilé comment j'ai finallement implémenté lees sources et les point réfléchissant :
- pour les reconnaîtres je met à la position voulue un coefficient de réfraction négatif pour les point réfléchissants et compris entre [0,1[ pour les sources
- lors du calcule des f_out, je teste les coefficient stockés dans la matrice pour traiter à part les deux cas, si le coefficient de refraction est supérieur ou égale à 1, je continue normallement le calcule
- pour les points réfléchissants, il n'y a qu'une façon de fonctionner
- pour les sources j'imagine que l'on pourrait créer des types de sources différents. Par exemple si le coeff de réfraction est entre [0, 0.5] le point est une source avec frequence f_1, s'il est entre ]0.5 , 1[ la source émet à une fréquence f_2. Pour l'instant je n'ai mit qu'un type de source.

il me semble que ça fonctionne plutôt bien, ça nous évite de calculer des f_out qui ne seront de toute façon pas utilisés et ça nous évite de stocké les sources dans une matrice et ou vecteur supplémentaire.
