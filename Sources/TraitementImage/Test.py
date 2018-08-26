from PIL import Image
import sys

# Commande pour lancer le code : python3 Test.py 1000 1000 1002 1002 5 10 1 7
# python3 nomDuCode startX startY endX endY precision EspaceImage IndiceRefractionBas indiceRefractionHaut

def afficher(matrice):
    for k in range(nbCouche):
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
    indice = (pMax - vPixel)/(pMax-pMin) * (bornSup-bornInf)+bornInf
    return indice

def calculeMinAndMax():
    pMin = 255
    pMax = 0
    for n in range(0,nImageEtudie):
        imag = Image.open(nomImage(n))
        cropImag = imag.crop((startX,startY,endX,endY))
        histo = cropImag.histogram()
        iter = 0
        for el in histo:
            if el != 0:
                if pMin>iter:
                    pMin = iter
                if pMax<iter:
                    pMax = iter
            iter = iter + 1
    return pMin,pMax

def afficherPixelImage():
    for n in range(0,nImageEtudie):
        imag = Image.open(nomImage(n))
        for y in range(startY,endY,1):
            for x in range(startX,endX,1):
                c = imag.getpixel((x,y))
                print(calculeIndice(c,1, 5))
        print()

nbImag = 1
nbCouche = 0

i1 = Image.open(nomImage(0))
(limag, himag) = i1.size


#Gestion des erreurs des paramètres.
messageErreur = "L'éxécution doit être sous cette forme : ''python3 Test.py debutX debutY finX finY précisionDésiré précisionEntreLesImages indiceRefractionBas indiceRefractionHaut''. "
if len(sys.argv)!=9:
    print("Le noumbre d'argument n'est pas correcte.", messageErreur)
    sys.exit(0)
else:
    startX = int(sys.argv[1])
    startY = int(sys.argv[2])
    endX = int(sys.argv[3])
    endY = int(sys.argv[4])
    precision = int(sys.argv[5])# Précision désiré lors de l'approximation linéaire
    EspaceImage = int(sys.argv[6]) #Précision entre les images fournies.
    bornInf = int(sys.argv[7]) #indice de réfraction le plus faible
    bornSup = int(sys.argv[8]) #indice de réfraction le plus haut
if (startX<0 or startY<0 or endX < 0 or endY<0):
    print("Erreur, vous avez donné une position dans l'image néagative.")
    sys.exit(0)
elif (startX>limag or startY>himag or endX>limag or endY>himag or startX>endX or startY>endY):
    print("Erreur, les dimensions du cropage sont incorrectes. L'image fait de taille ", limag, " x ", himag)
    sys.exit(0)

#Initialisation de taille des matrices
tailleMatriceX = endX-startX
tailleMatriceY = endY-startY


nbImag = 1
nbCouche = 0
nImageEtudie = 5

#Calcule de la partie de l'histogramme utilisé
[pMin,pMax] = calculeMinAndMax()

#afficherPixelImage()

mat = [[[0 for i in range (200)] for j in range (tailleMatriceY)] for k in range (tailleMatriceX)]
for w in range(1,nImageEtudie):
    nbImag = nbImag+1
    name = nomImage(w)
    i2 = Image.open(name)
    while(precision*nbCouche <= w*EspaceImage):
        for y in range(startY,endY,1):
            for x in range(startX,endX,1):
                c1 = i1.getpixel((x,y))
                c2 = i2.getpixel((x,y))
                indice1 = calculeIndice(c1,bornInf, bornSup)
                indice2 = calculeIndice(c2,bornInf, bornSup)
                # fait l'appproximation linéaire
                ind = (10-(nbCouche*precision-(nbImag-2)*10))/10*indice1+(10-((nbImag-1)*10-nbCouche*precision))/10*indice2
                mat[x-startX][y-startY][nbCouche] = ind
        nbCouche = nbCouche + 1
    i1 = i2

print("Noubre de Couche ", nbCouche)
#img.show()
#afficher(mat)
writeLog(mat)

