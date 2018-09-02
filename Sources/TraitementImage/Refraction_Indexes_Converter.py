#!/usr/bin/python
import PIL as pillow
from PIL import Image
from PyQt4 import QtGui, QtCore
import sys
import os


# Commande pour lancer le code : python3 Test.py 1000 1000 1002 1002 5 10 1 7
# python3 nomDuCode startX startY endX endY precision EspaceImage IndiceRefractionBas indiceRefractionHaut
directory = "./"    #rapresenting the directory containing the images to convert
directory2 = "./"   #rapresenting the directory where the log file will be created
startdir = os.getcwd() #current directory
buttonx = 0      #boolean defining if the event closewindow is triggered by the X button or by the apply button.



#class Widget define the main window of the GUI and his fonction.


class Widget(QtGui.QDialog) :

    def __init__(self, parent=None):
        super(Widget, self).__init__(parent)

        global directory
        global directory2

        self.answer1 = QtGui.QLabel()   #defining startx point labels
        q1Edit = QtGui.QLineEdit()
        q1Edit.textChanged.connect(self.q1Changed)

        self.answer2 = QtGui.QLabel()   #defining starty point labels
        q2Edit = QtGui.QLineEdit()
        q2Edit.textChanged.connect(self.q2Changed)

        self.answer3 = QtGui.QLabel()   #defining endx point labels
        q3Edit = QtGui.QLineEdit()
        q3Edit.textChanged.connect(self.q3Changed)

        self.answer4 = QtGui.QLabel()   #defining endy point labels
        q4Edit = QtGui.QLineEdit()
        q4Edit.textChanged.connect(self.q4Changed)

        self.answer5 = QtGui.QLabel()   #defining distance between two pixels of the image labels
        q5Edit = QtGui.QLineEdit()
        q5Edit.textChanged.connect(self.q5Changed)

        self.answer6 = QtGui.QLabel()   #defining distance between two layers labels
        q6Edit = QtGui.QLineEdit()
        q6Edit.textChanged.connect(self.q6Changed)

        self.answer7 = QtGui.QLabel()   #defining white refraction index labels
        q7Edit = QtGui.QLineEdit()
        q7Edit.textChanged.connect(self.q7Changed)

        self.answer8 = QtGui.QLabel()   #defining black refraction index labels
        q8Edit = QtGui.QLineEdit()
        q8Edit.textChanged.connect(self.q8Changed)

        self.answer9 = QtGui.QLabel()   #defining numbers of images labels
        q9Edit = QtGui.QLineEdit()
        q9Edit.textChanged.connect(self.q9Changed)


        global grid
        grid = QtGui.QGridLayout()
        grid.setSpacing(20)

        #definition of all labels
        grid.addWidget(QtGui.QLabel('StartX'), 1, 0)
        grid.addWidget(q1Edit, 1, 1)

        grid.addWidget(QtGui.QLabel('StartY'), 2, 0)
        grid.addWidget(q2Edit, 2, 1)

        grid.addWidget(QtGui.QLabel('EndX'), 3, 0)
        grid.addWidget(q3Edit, 3, 1)

        grid.addWidget(QtGui.QLabel('EndY'), 4, 0)
        grid.addWidget(q4Edit, 4, 1)

        grid.addWidget(QtGui.QLabel('Distance between two pixels of the image'), 5, 0)
        grid.addWidget(q5Edit, 5, 1)

        grid.addWidget(QtGui.QLabel('Distance between two layers'), 6, 0)
        grid.addWidget(q6Edit, 6, 1)

        grid.addWidget(QtGui.QLabel('White refraction index'), 7, 0)
        grid.addWidget(q7Edit, 7, 1)

        grid.addWidget(QtGui.QLabel('Black refraction inde'), 8, 0)
        grid.addWidget(q8Edit, 8, 1)

        grid.addWidget(QtGui.QLabel('Number of images'), 9, 0)
        grid.addWidget(q9Edit, 9, 1)

        #definition of select directory buttons
        seldir = QtGui.QPushButton('Select directory of images', self)
        seldir.clicked.connect(self.selectdir)

        seldir2 = QtGui.QPushButton('Select directory where logfile will be created or updated', self)
        seldir2.clicked.connect(self.selectdir2)

        #definition of Apply button (trigger the fonction apply and the event closeWindow)
        applyBtn = QtGui.QPushButton('Apply', self)
        applyBtn.clicked.connect(self.apply)
        applyBtn.clicked.connect(self.close)

        #definition of starting properties of the window
        self.path = QtGui.QLabel(startdir)
        self.path2 = QtGui.QLabel(startdir)
        grid.addWidget(seldir,10,0)
        grid.addWidget(self.path, 10,1)
        grid.addWidget(seldir2,11,0)
        grid.addWidget(self.path2, 11,1)
        grid.addWidget(applyBtn,12,2)
        self.setLayout(grid)
        self.setGeometry(300, 300, 600, 800)
        self.setWindowTitle("refraction index convertion")
        app.aboutToQuit.connect(self.closeEvent)

    #fonction apply set the closeEvent boolean to 1
    def apply(self):
        global buttonx
        buttonx = 1

    #select the directory and store the path into the variable directory
    def selectdir(self):
        global directory
        directory = str(QtGui.QFileDialog.getExistingDirectory(self, "Select Directory"))
        self.path.setText(directory)

    #select the directory and store the path into the variable directory2
    def selectdir2(self):
        global directory2
        directory2 = str(QtGui.QFileDialog.getExistingDirectory(self, "Select Directory"))
        self.path2.setText(directory2)

    #show a message box if the buttonx variable is set to 0
    def closeEvent(self, event):
        if (buttonx == 0):
            msg = QtGui.QMessageBox()
            msg.setIcon(QtGui.QMessageBox.Critical)
            msg.setText("The progam has been shut down")
            msg.setStandardButtons(QtGui.QMessageBox.Ok)
            #msg.buttonClicked.connect(msgbtn)
            retval = msg.exec_()
            sys.exit(0)

# set all data entered by the user
    def q1Changed(self, text):
        self.answer1.setText(text)

    def q2Changed(self, text):
        self.answer2.setText(text)

    def q3Changed(self, text):
        self.answer3.setText(text)

    def q4Changed(self, text):
        self.answer4.setText(text)

    def q5Changed(self, text):
        self.answer5.setText(text)

    def q6Changed(self, text):
        self.answer6.setText(text)

    def q7Changed(self, text):
        self.answer7.setText(text)

    def q8Changed(self, text):
        self.answer8.setText(text)

    def q9Changed(self, text):
        self.answer9.setText(text)


    #return all data set by the user
    def returnAnswer1(self):
        return self.answer1.text()

    def returnAnswer2(self):
        return self.answer2.text()

    def returnAnswer3(self):
        return self.answer3.text()

    def returnAnswer4(self):
        return self.answer4.text()

    def returnAnswer5(self):
        return self.answer5.text()

    def returnAnswer6(self):
        return self.answer6.text()

    def returnAnswer7(self):
        return self.answer7.text()

    def returnAnswer8(self):
        return self.answer8.text()

    def returnAnswer9(self):
        return self.answer9.text()

    #return all the data entered by the user in a list. The first member of the list is the name of the file (sys.argv[1])
    @staticmethod
    def getData(parent=None):
        dialog = Widget(parent)
        dialog.exec_()
        return ["Refraction_Indexes_Converter.py", dialog.returnAnswer1(), dialog.returnAnswer2(), dialog.returnAnswer3(), dialog.returnAnswer4(), dialog.returnAnswer5(), dialog.returnAnswer6(), dialog.returnAnswer7(), dialog.returnAnswer8(),directory, dialog.returnAnswer9()]


#The fonction nomImage take as parameter num that correspond to the number of image that is currently treatise
#this fonction return the name of the image corresponding to the number num.
#the Image must be in the format Hynobius FIB SEM dataXXXX.tif, where X is an integer
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

#show a message box (information)
def newWindow(nC):
    msg = QtGui.QMessageBox()
    msg.setIcon(QtGui.QMessageBox.Information)
    msg.setText("Images' refraction index have been converted successfully")
    msginfo1 = str(nC)
    msginfo2 = "Number of layers: "
    msginfo = msginfo2 + msginfo1
    msg.setInformativeText(msginfo)
    msg.setStandardButtons(QtGui.QMessageBox.Ok)
    retval = msg.exec_()


#show a message box (Critical)
def errorwind(nerror):
    msg = QtGui.QMessageBox()
    msg.setIcon(QtGui.QMessageBox.Critical)
    if (nerror == 1):
        msg.setText("Error, number of arguments does not match.")
        msg.setInformativeText("Please fill all blank spaces")
    elif (nerror == 2):
        msg.setText("Error, negative coordinates are not allowed.")
    elif (nerror == 3):
        msginfo1 = "Error, position indexes out of range. Image size:  "
        msginfo2 = str(limag)
        msginfo3 = " x "
        msginfo4 = str(himag)
        msginfo = msginfo1 + msginfo2 + msginfo3 + msginfo4
        msg.setText(msginfo)
    msg.setStandardButtons(QtGui.QMessageBox.Ok)
    retval = msg.exec_()

#The fonction writeLog create or uptade a file named logfile.txt.
#this file contain SizeX, SizeY, SizeZ and all the refrction indexes of the image treatised.
#all datas are parsed by a space " "
def writeLog(matrice):
    os.chdir(directory2)
    file = open("logfile.txt","w+")
    file.truncate(0)
    file.write(str(tailleMatriceX))
    file.write(" ")
    file.write(str(tailleMatriceY))
    file.write(" ")
    file.write(str(nbCouche))
    file.write(" ")
    for l in range(nbCouche):
        for f in range(tailleMatriceY):
            for g in range(tailleMatriceX):
                file.write(str(matrice[g][f][l]))
                file.write(" ")
            #file.write("\n")
        #file.write("\n")
    file.close()

#Indique pour chaque pixel la valeur à prendre en indice de réfraction
def calculeIndice(vPixel):
    if vPixel>pMax: #pour du blanc
        indice = bornSup
    elif vPixel<pMin: #pour du gris foncé
        indice = bornInf
    else: #Pour le gris claire
        indice = (vPixel-pMin)/(pMax-pMin) *(bornSup-bornInf)+bornInf
    return indice

def calculeMinAndMax():
    histoTotal = [0 for i in range (256)]
    # Calcul de l'histogramme de toutes les images combinées
    for n in range(0,nImageEtudie):
        imag = Image.open(nomImage(n))
        cropImag = imag.crop((startX,startY,endX,endY))
        histo = cropImag.histogram()
        for i in range(256):
            histoTotal[i] = histoTotal[i] + histo[i]
    #print(len(histoTotal))
    c1 = [0,0,0] # [position du centre de la partie,nombre de pixel dans cette partie, somme des valeur des pixels]
    c2 = [0,0,0]
    c3 = [0,0,0]
    nvc1 = 60
    nvc2 = 110
    nvc3 = 150
    while(c1[0] != nvc1 or c2[0] != nvc2 or c3[0] != nvc3):
        c1 = [nvc1,0,0] # [position du centre de la partie,nombre de pixel dans cette partie, somme des valeur des pixels]
        c2 = [nvc2,0,0]
        c3 = [nvc3,0,0]
        # Crée les ensembles de chaque partie
        for i in range(256):
            if(histoTotal[i] != 0):
                if (abs(c1[0]-i)<=abs(c2[0]-i)):
                    c1[1] = c1[1]+histoTotal[i]
                    c1[2] = c1[2]+histoTotal[i]*i
                elif (abs(c2[0]-i)<abs(c3[0]-i)):
                    c2[1] = c2[1]+histoTotal[i]
                    c2[2] = c2[2]+histoTotal[i]*i
                else:
                    c3[1] = c3[1]+histoTotal[i]
                    c3[2] = c3[2]+histoTotal[i]*i
	#Calcule du nouveau centre de chaque partie.
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
#calcule de la limite entre la partie 1 et 2 (c-à-d la limite du gris foncé) et la limite entre la partie 2 et 3 (c-à-d la limite du blanc)
    pMin = int((nvc2-nvc1)/2+nvc1)
    pMax = int((nvc3-nvc2)/2+nvc2)
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
app = QtGui.QApplication([])
window = Widget()
sys.argv = window.getData()



#Gestion des erreurs des paramètres.
#messageErreur = "L'éxécution doit être sous cette forme : ''python3 Test.py debutX debutY finX finY précisionDésiré précisionEntreLesImages indiceRefractionBas indiceRefractionHaut''. "
for i in range(0,11):
    if (sys.argv[i] == ""):
        errorwind(1)
    #print("Le noumbre d'argument n'est pas correcte.", messageErreur)
        sys.exit(0)
startX = int(sys.argv[1])
startY = int(sys.argv[2])
endX = int(sys.argv[3])
endY = int(sys.argv[4])
precision = float(sys.argv[5])# Précision désiré lors de l'approximation linéaire
EspaceImage = float(sys.argv[6]) #Précision entre les images fournies.
bornInf = float(sys.argv[7]) #indice de réfraction le plus faible
bornSup = float(sys.argv[8]) #indice de réfraction le plus haut
chemin = str(sys.argv[9])
nImageEtudie = int(sys.argv[10])
os.chdir(chemin)
i1 = Image.open(nomImage(0))
(limag, himag) = i1.size
if (startX<0 or startY<0 or endX < 0 or endY<0):
    errorwind(2)
    #print("Erreur, vous avez donné une position dans l'image néagative.")
    sys.exit(0)
elif (startX>limag or startY>himag or endX>limag or endY>himag or startX>endX or startY>endY):
    errorwind(3)
    #print("Erreur, les dimensions du cropage sont incorrectes. L'image fait de taille ", limag, " x ", himag)
    sys.exit(0)


#Initialisation de taille des matrices
tailleMatriceX = endX-startX
tailleMatriceY = endY-startY


nbImag = 1
nbCouche = 0


#Calcule des limites du gris claire et du blanc
[pMin,pMax] = calculeMinAndMax()


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

                # fait l'appproximation linéaire
                vPixel = (10-(nbCouche*precision-(nbImag-2)*10))/10*c1+(10-((nbImag-1)*10-nbCouche*precision))/10*c2
                ind = calculeIndice(vPixel)
                mat[x-startX][y-startY][nbCouche] = ind
        nbCouche = nbCouche + 1
    i1 = i2


#img.show()
#afficher(mat)
writeLog(mat)
newWindow(nbCouche)
