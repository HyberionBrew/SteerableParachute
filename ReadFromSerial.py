# -*- coding: utf-8 -*-
"""
Created on Tue Apr  3 17:32:28 2018

@author: Fabian
Reads out from arduino Serial
"""

import serial
import csv

ser = serial.Serial('COM4',9600)
ser.flushInput()

filename = 'data.csv'
file = open(filename,'w+')
file.close()


fieldnames = ['MemoryAdress','Longitude', 'Latitude',"time","Altitude","ReceiverPos"]

with open(filename, 'a') as csvfile:
    writer = csv.writer(csvfile, delimiter=',',
                            quotechar=' ', quoting=csv.QUOTE_MINIMAL)
    while True:
        try:
            ser_bytes = ser.readline()
            decoded = str(ser_bytes.decode("utf-8"))
            decodedList = decoded.split(',')
            
           # dictionary = #dict(zip(fieldnames, decodedList))
            writer.writerow(decodedList)
            print(decodedList)
        except:
            #runs into execpet because @ the end double println @ arduino
            #results in exception from .split
            csvfile.close()
            ser.close()
            
            print("^C")
            break
            
            
ser.close()