
Ce fichier regroupe les explications de l'utilisation des trois programmes décrits dans le documents "Projet salamandre".
Y est ajouté une description d'un quatrième programme, 2d_wave_Graphic.cpp, que nous avons utilisé pour les tests de la LBM en deux dimensions.


Refraction_Indexes_Converter.py :

  Refraction_Indexes_Converter.py est un fichier qui extrait les indices de réfraction de plusieurs couches du tissu des poches d'oeufs de salamandre Hida à partir d'une image.
  Le programme écrit les données collectées dans un fichier logfile.txt.
  Une fois le code exécuté, l'utilisateur doit rentrer les paramètres demandés par la GUI, en particulier :
  - StartX : le point de départ sur l'axe x pour définir la zone de l'image à considérer
  - StartY : le point de depart sur l'axe y pour définir la zone de l'image à considérer
  - EndX : le point sur l'axe x qui définit la fin de la zone de l'image à considérer
  - EndY : le point sur l'axe y qui définit la fin de la zone de l'image à considérer
  - Distance between two pixels of the image : définit la distance en nanomètres entre deux pixels
  - Distance between two layers : définit la distance en nanomètres entre deux couches
  - White refraction index : indice de réfraction de la partie plus claire de l'image
  - Black refraction index : indice de réfraction de la partie plus sombre de l'image
  - Number of images : nombre d'images dont on doit effectuer la conversion


  Exécution du programme :

    (pour Linux)
      le code peut être exécuté directement à partir du fichier exécutable Refracrion_Index_Converter.
      Il peut aussi être exécuté depuis la ligne de commande : python3 Refraction_Index_Converter.py

    (pour Window)
      Le code peut être exécuté à partir de python IDLE (https://www.python.org/downloads)

    Prérequis pour exécuter le programme (pas requis si lancé depuis l'exécutable) :
      - librairie PIL
      - librairie PyQt4 (sudo apt-get install python3-PyQt4)


    Ecriture du logfile :
      Les premières lignes du logfile contiennent les dimensions de la matrice (sizeX, sizeY, sizeZ), puis les valeurs utilisées pour le calcul du coefficient de réfraction :
      bornInf et bornSup sont les indices de réfractions des pixels foncés et clairs respectivement.
      pMin et pMax sont les valeurs frontières calculées par la méthode 3-moyenne, qui séparent les trois groupes de pixels.

      Viennent ensuite les indices de réfractions regroupés par couches.
      Chaque couche contient une ligne par valeur de y (sizeY lignes).
      Chaque ligne contient un indice de réfraction par valeur de x (sizeX indices par couche). Les indices sont séparés par un espace " ".


    Attention !
      L'exécution du code se termine par l'affichage d'une fenêtre pop-up.
      Si le programme est lancé depuis la console, la progression est affichée dans la console.
      Si le programme est lancé en utilisant l'exécutable, la progression n'est pas affichée, il faut donc attendre l'apparition de la fenêtre pop-up pour savoir que le programme est terminé, ce qui peut prendre longtemps.



LogfileReader.py : 
  LogfileReader.py est un fichier qui permet d'afficher une couche de la matrice des indices de réfraction contenue dans le logfile.txt.
Le programme demande à l'utilisateur de choisir la couche à traiter. Il affiche cette dernière en transformant les indices de réfraction en valeur de pixel noir et blanc. Veuillez prendre en compte que la valeur des pixels clairs prend pour valeur la moins élevée possible (la valeur la plus sombre pour leur partie). Alors que les pixels foncés prennent la valeur la plus élevée (la valeur la plus clair pour leur partie). Ceci explique le faible contraste de l’image crée. Veuillez consultez la figure n°5 pour plus de compréhension. 


Exécution du programme :

    (pour Linux)
      Le code peut être exécuté depuis la ligne de commande : python3 LogfileReader.py

    (pour Window)
      Le code peut être exécuté à partir de python IDLE (https://www.python.org/downloads)

    Prérequis pour exécuter le programme :
      - librairie PIL
      - librairie PyQt4 (sudo apt-get install python3-PyQt4)









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
