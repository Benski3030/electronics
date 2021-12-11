import csv
import serial
import time

logfile = open(r"/home/pi/pitemp/temps.csv", "a")
ser = serial.Serial(port = "/dev/ttyACM0", baudrate = 9600, timeout = 60)

while 1:
    line = ser.readline().strip("\n") 
    now = time.strftime("%d/%m/%Y %H:%M:%S", time.localtime())
    a =  "%s, %s" % (now, line)
    logfile.write(a)
    logfile.flush()    
logfile.close()
ser.close()
