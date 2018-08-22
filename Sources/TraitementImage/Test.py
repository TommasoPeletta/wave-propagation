from PIL import Image
import sys


def afficher(matrice):
    for k in range(14):
        for x in range(tailleMatriceX):
            for y in range(tailleMatriceY):
                print(matrice[x][y][k], end=' ')
            print("")
        print("")

def nomImage(num):
    s1 = "Hynobius FIB SEM data"
    s3 = ".tif"
    saux1 = "0"
    saux2 = "00"
    saux3 = "000"
    s2 = str(num)
    if num//10 == 0:
        s2 = saux3+s2
    elif num//100 == 0:
        s2 = saux2+s2
    elif num//1000 == 0:
        s2 = saux1+s2
    return s1+s2+s3


def writeLog(matrice):
    file = open("logfile.txt","r+")
    file.truncate(0)
    for l in range(nbCouche):
        for f in range(tailleMatriceY):
            for g in range(tailleMatriceX):
                file.write(str(matrice[g][f][l]))
                file.write(" ")
            file.write("\n")
        file.write("\n")
    file.close()

def calculeIndice(vPixel, bornInf, bornSup):
    if (vPixel <= 80):
        indice = (255 - vPixel)/255 * (bornSup-bornSup*0.8)+bornSup*0.8
    elif (vPixel >= 175):
        indice = (255 - vPixel)/255* (bornSup*0.2-bornInf)+bornInf
    else:
        indice = (255 - vPixel)/255 * (bornSup-bornInf)+bornInf
    return indice


tailleCouche = 10
precision = 3
nbImag = 1
nbCouche = 0

i1 = Image.open(nomImage(0))
(limag, himag) = i1.size

#Gestion des erreurs des paramètres.
messageErreur = "L'éxécution doit être sous cette forme : ''python3 Test.py debutX debutY finX finY précisionDésiré précisionEntreLesImages''. "
if len(sys.argv)!=7:
    print("Le noumbre d'argument n'est pas correcte.", messageErreur)
    sys.exit(0)
else:
    startX = int(sys.argv[1])
    startY = int(sys.argv[2])
    endX = int(sys.argv[3])
    endY = int(sys.argv[4])
    precision = int(sys.argv[5])# Précision désiré lors de l'approximation linéaire
    tailleCouche = int(sys.argv[6]) #Précision entre les images fournies.
if (startX<0 or startY<0 or endX < 0 or endY<0):
    print("Erreur, vous avez donné une position dans l'image néagative.")
    sys.exit(0)
elif (startX>limag or startY>himag or endX>limag or endY>himag or startX>endX or startY>endY):
    print("Erreur, les dimensions du cropage sont incorrectes.")
    sys.exit(0)

#Initialisation de taille des matrices
tailleMatriceX = endX-startX
tailleMatriceY = endY-startY


nbImag = 1
nbCouche = 0

mat = [[[0 for i in range (200)] for j in range (tailleMatriceY)] for k in range (tailleMatriceX)]
for w in range(1,10):
    nbImag = nbImag+1
    name = nomImage(w)
    i2 = Image.open(name)
    bornInf = 1
    bornSup = 10
    #img = Image.new("L",(200,200),color=0)
    while(precision*nbCouche <= w*tailleCouche):
        for y in range(startY,endY,1):
            for x in range(startX,endX,1):
                c1 = i1.getpixel((x,y))
                c2 = i2.getpixel((x,y))
                #img.putpixel((x-300, y-300), c)
                indice1 = calculeIndice(c1,bornInf, bornSup)
                indice2 = calculeIndice(c2,bornInf, bornSup)
                #indice1 = (255 - c1)/255 * (bornSup-bornInf)+bornInf
                #indice2 = (255 - c2)/255 * (bornSup-bornInf)+bornInf
                # fait l'appproximation linéaire
                ind = (10-(nbCouche*3-(nbImag-2)*10))/10*indice1+(10-((nbImag-1)*10-nbCouche*3))/10*indice2
                mat[x-startX][y-startY][nbCouche] = ind
        nbCouche = nbCouche + 1
    i1 = i2

print("Noubre de Couche ", nbCouche)
#img.show()
#afficher(mat)
writeLog(mat)

