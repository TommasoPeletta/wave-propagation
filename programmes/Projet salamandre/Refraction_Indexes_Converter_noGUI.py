#!/usr/bin/python
import PIL as pillow
from PIL import Image
import sys
import os

# Command to launch the program : python3 Refraction_Indexes_Converter_noGUI.py <StartX> <StartY> <EndX> <EndY> <Distance between two pixels of the image> <Distance between two layers> <White refraction index> <Black refraction index> <Number of images> <Select directory of images> <Select directory where logfile will be created or updated>

directory = "./"    #representing the directory containing the images to convert
startdir = os.getcwd() #current directory
directory2 = startdir   #representing the directory where the log file will be created


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

def progbar(current, total, full_progbar):
    frac = current/total
    filled_progbar = round(frac*full_progbar)
    print('\r', '#'*filled_progbar + '-'*(full_progbar-filled_progbar) +" "+ str(current) + " images traitées sur "+ str(total), '[{:>7.2%}]'.format(frac), end='')

def progbarKMean(current, total, full_progbar, message):
    frac = current/total
    filled_progbar = round(frac*full_progbar)
    print('\r', message +"  "+'#'*filled_progbar + '-'*(full_progbar-filled_progbar), '[{:>7.2%}]'.format(frac), end='')

def progbarlog(current, total, full_progbar):
    frac = current/total
    filled_progbar = round(frac*full_progbar)
    print('\r', '#'*filled_progbar + '-'*(full_progbar-filled_progbar) +" "+ str(current) + " nombre de couche écrites sur "+ str(total), '[{:>7.2%}]'.format(frac), end='')


#The fonction writeLog create or uptade a file named logfile.txt.
#this file contain SizeX, SizeY, SizeZ and all the refractive indexes of the image treatised.
#all datas are parsed by a space " "

def writeLog(matrice):
    os.chdir(startdir)
    os.chdir(directory2)
    file = open("logfile.txt","w+")
    file.truncate(0)
    file.write("SizeX, SizeY, SizeZ : ")
    file.write("\n")
    file.write(str(tailleMatriceX))
    file.write(" ")
    file.write(str(tailleMatriceY))
    file.write(" ")
    file.write(str(nbCouche))
    file.write("\n")
    file.write("bornInf, bornSup, pMin, pMax : ")
    file.write("\n"+str(bornInf) + " "+ str(bornSup) + " "+ str(pMin)+ " "+ str(pMax) + "\n")
    for l in range(nbCouche):
        progbar(l+1,nbCouche, 20)
        sys.stdout.flush()
        file.write("N Couche " + str(l) + " : " + "\n")
        for f in range(tailleMatriceY):
            for g in range(tailleMatriceX):
                file.write(str(matrice[g][f][l]))
                file.write(" ")
            file.write("\n")
        file.write("\n")
    file.close()



#fonction that calculate refraction index from the value of the pixel.
# -vPixel of type float contain the value of the pixel (from 0 to 255).
def calculeIndice(vPixel):
    if vPixel>pMax: #the white part
        indice = bornSup
    elif vPixel<pMin: #the black part
        indice = bornInf
    else: #the gray part
        indice = (vPixel-pMin)/(pMax-pMin) *(bornSup-bornInf)+bornInf
    return indice



# fonction that use k-mean clustering to calculate the limite between white, gray and black (K = 3).
# -pMin represent the limite between black and gray
#- pMax represent the limite between gray and white.
def calculeMinAndMax():
    histoTotal = [0 for i in range (256)]
    #Generation of a histogram that combine each histogram of each picture.
    for n in range(0,nImageEtudie):
        imag = Image.open(nomImage(n))
        # we only keep the part of the picture which is defined by the user.
        cropImag = imag.crop((startX,startY,endX,endY))
        histo = cropImag.histogram()
        for i in range(256):
            histoTotal[i] = histoTotal[i] + histo[i]
        progbarKMean(n,nImageEtudie, 20, "Parcours de toutes les images")
        sys.stdout.flush()
    c1 = [0,0,0] # part n°1, [Position of the center of the part,nombre of value inside of the part, sum of pixel's value of the part]
    c2 = [0,0,0] # part n°2
    c3 = [0,0,0] # part n°3
    nvc1 = 60 # starting random position
    nvc2 = 110
    nvc3 = 150
    while(c1[0] != nvc1 or c2[0] != nvc2 or c3[0] != nvc3): #if a new position is calculate
        c1 = [nvc1,0,0]
        c2 = [nvc2,0,0]
        c3 = [nvc3,0,0]
        for i in range(256): #for each value of the histogram
            if(histoTotal[i] != 0):
                # chose the good groop, the good part
                if (abs(c1[0]-i)<=abs(c2[0]-i)):
                    c1[1] = c1[1]+histoTotal[i]
                    c1[2] = c1[2]+histoTotal[i]*i
                elif (abs(c2[0]-i)<abs(c3[0]-i)):
                    c2[1] = c2[1]+histoTotal[i]
                    c2[2] = c2[2]+histoTotal[i]*i
                else:
                    c3[1] = c3[1]+histoTotal[i]
                    c3[2] = c3[2]+histoTotal[i]*i
        # new center position calcul for each group
        if c1[1]!=0:
            nvc1 = c1[2]/c1[1]
        else:
            nvc1 = c1[0]
        if c2[2]!=0:
            nvc2 = c2[2]/c2[1]
        else:
            nvc2 = c2[0]
        if c3[1]!=0:
            nvc3 = c3[2]/c3[1]
        else:
            nvc3 =  c3[0]
    #When center positions dont change, calcul of the limit between 2 parts.
    pMin = int((nvc2-nvc1)/2+nvc1)
    pMax = int((nvc3-nvc2)/2+nvc2)
    progbarKMean(nImageEtudie,nImageEtudie, 20, "Algorithme de K-mean clustering")
    sys.stdout.flush()
    return pMin,pMax



nbImag = 1 #represent the nombre of picture that were already used for the génération of refraction index layer
nbCouche = 0 #represent the nombre of refraction index layer calculate


#Management of parameter
for i in range(0,12):
    if (sys.argv[i] == ""): #wrong nombre of parameter
        print("Error, number of arguments does not match.")
        sys.exit(0)
startX = int(sys.argv[1])
startY = int(sys.argv[2])
endX = int(sys.argv[3])
endY = int(sys.argv[4])
precision = float(sys.argv[5])# Precision for linear approximation
EspaceImage = float(sys.argv[6]) # space between picture.
bornInf = float(sys.argv[7]) #refractive index for black pixel
bornSup = float(sys.argv[8]) #refractive index for white pixel (water)
nImageEtudie = int(sys.argv[9])
chemin = str(sys.argv[10])#path to the directory where are the pictures
directory2 = str(sys.argv[11])
os.chdir(chemin)
i1 = Image.open(nomImage(0))
(limag, himag) = i1.size
if (startX<0 or startY<0 or endX < 0 or endY<0):  #wrong dimension for cropping
    print("Error, negative coordinates are not allowed.")
    sys.exit(0)
elif (startX>limag or startY>himag or endX>limag or endY>himag or startX>endX or startY>endY): #wrong dimension for cropping
    print("Error, position indexes out of range. Image size:  " + limag + " x "+himag)
    sys.exit(0)


#Initiation of the size of matrix
tailleMatriceX = endX-startX
tailleMatriceY = endY-startY


#calcul of limit between white, gray and black
print("Calcule des limites entre le blanc, gris, noir avec K mean clustering ...")
[pMin,pMax] = calculeMinAndMax()

#matrix where will be result
#(EspaceImage/precision)*nImageEtudie is the maximum  number of layer.
mat = [[[0 for i in range (int((EspaceImage/precision)*nImageEtudie))] for j in range (tailleMatriceY)] for k in range (tailleMatriceX)]


print("\n Nombre d'image à traiter : ", nImageEtudie)
#Generation of refractive index layer
#look over the nomber of picture defined by the user
#To have the precision defined by the user, the programm uses a linear approximation. 2 pictures are used for linear approximation (i1 and i2).
progbar(1,nImageEtudie, 20)
sys.stdout.flush()
for w in range(1,nImageEtudie):
    progbar(w+1,nImageEtudie, 20)
    sys.stdout.flush()
    nbImag = nbImag+1
    name = nomImage(w)
    i2 = Image.open(name)
    while(precision*nbCouche <= w*EspaceImage):
        for y in range(startY,endY,1):
            for x in range(startX,endX,1):
                c1 = i1.getpixel((x,y))
                c2 = i2.getpixel((x,y))

                # linear approximation
                vPixel = (EspaceImage-(nbCouche*precision-(nbImag-2)*EspaceImage))/EspaceImage*c1+(EspaceImage-((nbImag-1)*EspaceImage-nbCouche*precision))/EspaceImage*c2
		# transform the value of the pixel into refractive index
                ind = calculeIndice(vPixel)
                mat[x-startX][y-startY][nbCouche] = ind
        nbCouche = nbCouche + 1
    i1 = i2

print("\n Nombre de couches générés : ",nbCouche)
#write the result into a logfile.txt
print("\n Ecriture des résultats dans le logfile.txt ...")
writeLog(mat)
print("\n"+"Images' refraction index have been converted successfully")
#for i in range(100000+1):
#    progbar(i,100000, 20)
#    sys.stdout.flush()
print("\n")
