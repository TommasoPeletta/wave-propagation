#!/usr/bin/python
import PIL as pillow
from PIL import Image
import sys
import os

#this program draw a layer selected by the user.

# to run the program : python3 LogFileReader.py number_of_layer_to_show





#Management of parameter
for i in range(0,2):
    if (sys.argv[i] == ""): #wrong nombre of parameter
        print("Error, number of arguments does not match.")
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
