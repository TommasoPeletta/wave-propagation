from PIL import Image

tailleMatrice = 200
def afficher(matrice):
    for k in range(14):
        for x in range(tailleMatrice):
            for y in range(tailleMatrice):
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
    for l in range(14):
        for f in range(tailleMatrice):
            for g in range(tailleMatrice):
                file.write(str(matrice[g][f][l]))
                file.write(" ")
            file.write("\n")
        file.write("\n")
    file.close()


tailleCouche = 10
precision = 3
nbImag = 1
nbCouche = 0

mat = [[[0 for i in range (14)] for j in range (tailleMatrice)] for k in range (tailleMatrice)]
i1 = Image.open(nomImage(0))
for w in range(1,5):
    nbImag = nbImag+1
    print(w)
    name = nomImage(w)
    i2 = Image.open(name)
    bornInf = 1
    bornSup = 10
    #(l, h) = i.size
    #img = Image.new("L",(200,200),color=0)
    while(precision*nbCouche <= w*tailleCouche):
        for y in range(300,300+tailleMatrice,1):
            for x in range(300,300+tailleMatrice,1):
                c1 = i1.getpixel((x,y))
                c2 = i2.getpixel((x,y))
                #img.putpixel((x-300, y-300), c)
                indice1 = (255 - c1)/255 * (bornSup-bornInf)+bornInf
                indice2 = (255 - c2)/255 * (bornSup-bornInf)+bornInf
                # fait l'appproximation linéaire
                ind = (10-(nbCouche*3-(nbImag-2)*10))/10*indice1+(10-((nbImag-1)*10-nbCouche*3))/10*indice2
                mat[x-300][y-300][nbCouche] = ind
        nbCouche = nbCouche + 1
    i1 = i2

print("Noubre de Couche ", nbCouche)
#img.show()
#afficher(mat)
writeLog(mat)
