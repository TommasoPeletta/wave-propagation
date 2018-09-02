Ce fichier regroupe les explications de l'utilisation des deux programme décrits dans le documents "Projet salamandre".
Y est ajouté une description d'un troisième programme, 2d_wave_Graphic.cpp, que nous avons utilisé pour les tests de la LBM en deux dimensions.

Refraction_Indexes_Converter.py :

Refraction_Indexes_Converter.py est un fichier qui extrait les indices de réfraction de plusieurs couches du tissu des poches d'oeufs de salamandre Hida à partir d'une image.
Le programme écrit les données collectées dans un fichier logfile.txt.
Une fois le code exécuté, l'utilisateur doit rentrer les paramètres demandés par la GUI, en particulier :
-StartX : le point de départ sur l'axe x pour définir la zone de l'image à considérer 
-StartY : le point de depart sur l'axe y pour définir la zone de l'image à considérer
-EndX : le point sur l'axe x qui définit la fin de la zone de l'image à considérer
-EndY : le point sur l'axe y qui définit la fin de la zone de l'image à considérer
-Distance between two pixels of the image : définit la distance en nanomètres entre deux pixels
-Distance between two layers : définit la distance en nanomètres entre deux couches
-White refraction index : indice de réfraction de la partie plus claire de l'image
-Black refraction index : indice de réfraction de la partie plus sombre de l'image
-Number of images : nombre d'images dont on doit effectuer la conversion

Exécution du programme : 
(pour Linux)
le code peut être exécuté directement à partir du fichier exécutable Refracrion_Index_Converter.
Il peut aussi être exécuté depuis la ligne de commande : python3 Refraction_Index_Converter.py

(pour Window)
Le code peut être exécuté à partir de python IDLE (https://www.python.org/downloads)

Prérequis pour exécuter le programme (pas requis si lancé depuis l'exécutable) :
- librarie PIL
- librarie PyQt4 (sudo apt-get install python3-PyQt4)

Ecriture du logfile :
Le logfile contient la dimension de la matrice contenant les indices de réfraction (sizeX, sizeY, sizeZ), et les indices de réfraction de la matière. Toutes les données sont séparées par un espace " ".
les indices de réfraction sont écrites dans l'ordre de cette boucle:

for l in range(sizeZ):
        for f in range(sizeY):
            for g in range(sizeX):
                file.write(str(matrice[g][f][l]))
                file.write(" ")

Attention!
L'exécution du code se termine par l'affichage d'une fenêtre pop-up. (il peut prendre beaucoup de temps si beaucoup d'images sont données)






3d_wave.cpp :

3d_wave.cpp est un fichier qui recueille les données extraites des images dans le fichier logfile.txt et les stoque dans une matrice tabl_n. Les dimensions de la matrice sont extraites directement depuis logfile.txt.
Le fichier contient aussi la méthode de Boltzmann sur réseaux en trois dimensions que nous avons implémentée.
Les conditions aux bords sont gérées dans la procédure vector_cpy et à l'aide de la matrice d'atténuation beta.
Les conditions aux bords sont par défaut implémentées de façon à être périodiques dans les trois directions, donc sans atténuation.
Les points de la matrice tabl_n possédant un indice de réfraction strictement compris entre 0 et 1 sont considérés comme des sources, tandis que les points dont la valeur est inférieure ou égale à 0 sont considérés comme des miroirs.
La méthode de Boltzmann s'applique sur la matrice tabl_n qui contient les valeurs des indices de réfraction extraites de logfile.txt. Les données extraites n'ayant pas de source par défaut, la méthode ne fait donc rien.
Il est aussi possible d'utiliser ce fichier sans les données du logfile. Il faut alors retirer la procédure Hynobius() de la fonction main, les dimensions de la matrices sont alors déterminées dans la procédure allocate

Pour compiler le programme, il faut utiliser la commande : g++ 3d_wave.cpp -o 3d_wave
Il faut alors s'assurer que le fichier logfile.text se trouve dans le même dossier que l'exécutable 3d_wave (sauf si on veut utiliser le programme sans les données d'un logfile).
On peut alors lancer le programme avec la commande : ./3d_wave




2d_wave_Graphic.cpp :

2d_wave_Graphic.cpp est le fichier que nous avons utilisé pour les tests de notre implémentation de la LBM en deux dimensions.
Il utilise la librairie SpcTools pour l'affichage graphique et nécessite donc que le dossier SpcTools soit présent dans le dossier HOME de l'utilisateur.

Plusieurs procédures pour initialiser la matrice contenant les coéfficients de réfractions peuvent être appelées dans la fonction main(), les valeurs de sizeX et sizeY doivent parfois être adaptées à l'expérience que l'on veut reproduire.

La gestion des conditions au bord se fait dans la procédure vector_cpy et à l'aide de la matrice beta.

Pour compiler le programme, il faut utiliser la commande : make 3d_wave
Il est alors possible de lancer le programme avec la commande : ./wave






