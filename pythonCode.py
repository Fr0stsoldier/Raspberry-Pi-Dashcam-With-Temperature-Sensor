import datetime as dt
import picamera
import serial
import os
import time
ser = serial.Serial('/dev/ttyACM0', 9600)
camera = picamera.PiCamera(resolution=(800, 480), framerate=30)
camera.start_preview()
camera.start_recording('1.h264')
#for i in range (2, 6):
i = 0
mainVar = True
while mainVar:
    dx = dt.datetime.now()
    variable = ser.readline()
    vary = variable[0:5]
    varz = variable[7:8]    
    while (dt.datetime.now() - dx).seconds < 5:
        camera.annotate_text = ((dt.datetime.now().strftime('%m-%d-%Y %H:%M:%S')) + " " + vary)
        camera.wait_recording(.2)
    camera.split_recording('%d.h264' % i)
    i += 1
    if varz == '1':
        camera.stop_recording()
        camera.stop_preview()
        mainVar = False
        time.sleep(2)
        os.system("sudo poweroff")
    elif varz == '2':
        camera.stop_recording()
        camera.annotate_text = ("Recording stopped! press 1 to continue recording or 2 to poweroff")
        x = input
        if x == 1:
            break
        if x == 2:
            camera.stop_preview()
            mainVar = False
            time.sleep(2)
            os.system("Sudo poweroff")
    else:
        pass
