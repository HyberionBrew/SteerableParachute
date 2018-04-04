# -*- coding: utf-8 -*-
"""
Created on Wed Apr  4 2018

@author: Fabian
"""

import csv 
import matplotlib.pyplot as plt

with open('datamodified.csv') as f:
    reader = csv.reader(f)
    Longitude = []
    Latitude = []
    Altitude =[]
    for row in reader:
        if len(row)> 1 and int(row[0])<250:
            Longitude.append(int(row[1]))
            Latitude.append(int(row[2]))
            Altitude.append(row[4])
    print(Longitude)
    print(Latitude)
    print(Altitude)
    
#for i in range(0,len(Longitude)-1) :
plt.scatter(Longitude,Latitude)
#plt.axis(min(Longitude)-10,max(Longitude)+10,min(Latitude)-10,max(Latitude)+10)
plt.show()