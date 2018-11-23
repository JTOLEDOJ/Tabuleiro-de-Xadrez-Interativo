import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

sp1 = 33
sp2 = 35
sp3 = 37
sn1 = 36
sn2 = 38
sn3 = 40
i = 0
j = 0

# POSITIVO 
GPIO.setup(sp1, GPIO.OUT)
GPIO.setup(sp2, GPIO.OUT)
GPIO.setup(sp3, GPIO.OUT)

# NEGATIVO
GPIO.setup(sn1, GPIO.OUT)
GPIO.setup(sn2, GPIO.OUT)
GPIO.setup(sn3, GPIO.OUT)

def select(s):
    if s==0:
        GPIO.output(sp1, 0)
        GPIO.output(sp2, 0)
        GPIO.output(sp3, 0)
    elif s==1:
        GPIO.output(sp1, 1)
        GPIO.output(sp2, 0)
        GPIO.output(sp3, 0)
    elif s==2:
        GPIO.output(sp1, 0)
        GPIO.output(sp2, 1)
        GPIO.output(sp3, 0)
    elif s==3:
        GPIO.output(sp1, 1)
        GPIO.output(sp2, 1)
        GPIO.output(sp3, 0)
    elif s==4:
        GPIO.output(sp1, 0)
        GPIO.output(sp2, 0)
        GPIO.output(sp3, 1)
    elif s==5:
        GPIO.output(sp1, 1)
        GPIO.output(sp2, 0)
        GPIO.output(sp3, 1)
    elif s==6:
        GPIO.output(sp1, 0)
        GPIO.output(sp2, 1)
        GPIO.output(sp3, 1)
    elif s==7:
        GPIO.output(sp1, 1)
        GPIO.output(sp2, 1)
        GPIO.output(sp3, 1)
    return

def select2(s):
    if s==0:
        GPIO.output(sn1, 0)
        GPIO.output(sn2, 0)
        GPIO.output(sn3, 0)
    elif s==1:
        GPIO.output(sn1, 1)
        GPIO.output(sn2, 0)
        GPIO.output(sn3, 0)
    elif s==2:
        GPIO.output(sn1, 0)
        GPIO.output(sn2, 1)
        GPIO.output(sn3, 0)
    elif s==3:
        GPIO.output(sn1, 1)
        GPIO.output(sn2, 1)
        GPIO.output(sn3, 0)
    elif s==4:
        GPIO.output(sn1, 0)
        GPIO.output(sn2, 0)
        GPIO.output(sn3, 1)
    elif s==5:
        GPIO.output(sn1, 1)
        GPIO.output(sn2, 0)
        GPIO.output(sn3, 1)
    elif s==6:
        GPIO.output(sn1, 0)
        GPIO.output(sn2, 1)
        GPIO.output(sn3, 1)
    elif s==7:
        GPIO.output(sn1, 1)
        GPIO.output(sn2, 1)
        GPIO.output(sn3, 1)
    return

while(1):
    for i in range(8):
        select(i)
        print(i)

        for j in range(8):
            select2(j)
            time.sleep(0.1)