#!/usr/bin/python
import PIL as pillow
from PIL import Image
from PyQt4 import QtGui, QtCore
import sys
import os

#this program draw a layer celected by the user.

# to run the program : python3 LogFileReader.py
# A window will appear. You have to write the number of the layer that you want to draw.
# number of layer start at 0.

#class Widget define the main window of the GUI and his fonction.
class Widget(QtGui.QDialog) :

	def __init__(self, parent=None):
		super(Widget, self).__init__(parent)
		self.answer1 = QtGui.QLabel()   #defining the number of the layer that we want to draw
		q1Edit = QtGui.QLineEdit()
		q1Edit.textChanged.connect(self.q1Changed)
		grid = QtGui.QGridLayout()
		grid.setSpacing(20)
		#definition of the label
		grid.addWidget(QtGui.QLabel('Numéro de la couche à transformer en photo'), 1, 0)
		grid.addWidget(q1Edit, 1, 1)

		#define apply button
		applyBtn = QtGui.QPushButton('Apply', self)
		applyBtn.clicked.connect(self.close)
		grid.addWidget(applyBtn,2,2)
		self.setLayout(grid)
		self.setGeometry(100, 100, 100, 100)
		self.setWindowTitle("Creation image à partir du logfile.txt")
		app.aboutToQuit.connect(self.closeEvent)


# set all data entered by the user
	def q1Changed(self, text):
		self.answer1.setText(text)

	def returnAnswer1(self):
		return self.answer1.text()
	@staticmethod
	def getData(parent=None):
		dialog = Widget(parent)
		dialog.exec_()
		return ["Refraction_Indexes_Converter.py", dialog.returnAnswer1()]

app = QtGui.QApplication([])
window = Widget()
sys.argv = window.getData()



#Management of parameter
for i in range(0,2):
    if (sys.argv[i] == ""): #wrong nombre of parameter
        errorwind(1)
        sys.exit(0)
numCouche = int(sys.argv[1])

sizeX = 0
sizeY = 0
sizeZ = 0
nligne = 0
fligne = 0
l = 0
#reading of the logfile
f = open('logfile.txt')
lines = f.readlines()
i = 1
for line in lines:
	ligne = line.split()
	if i == 2:
		#save the size of the layer
		sizeX = int(ligne[0])
		sizeY = int(ligne[1])
		sizeZ = int(ligne[2])
		nligne = numCouche*(sizeY+2)+6
		fligne = ((numCouche+1)*(sizeY+2)+3)
		#initialize image
		Imag = Image.new('L',(sizeX,sizeY),color=0)
		print("sizeY " + str(sizeY))
		if numCouche >= sizeZ:
			print("le numéro de la couche n'est pas valable. Le numéro des couches commence à 0.")
			break
	if i==4:
		#save the minimum and maximum refractive index
		bornInf = float(ligne[0])
		bornSup = float(ligne[1])
		# value of the limite between black and gray and the limit between gray and white
		pMin = int(ligne[2])
		pMax = int(ligne[3])
	#draw the picture
	if i >= nligne and i <= fligne:
		for x in range(sizeX):
			ind = float(ligne[x])
			if ind==bornInf:
				Imag.putpixel((x,l),pMin)
			elif ind==bornSup:
				Imag.putpixel((x,l),pMax)
			else:
				#approximation linéaire inverse
				val = (ind-bornInf)*(pMax-pMin)/(bornSup-bornInf)+pMin
				Imag.putpixel((x,l),int(val))
		l = l +1
	i = i+1
#draw the picture
Imag.show()
