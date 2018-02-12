import serial
ser = serial.Serial('/dev/cu.usbmodemM4321001', 9600)

import time
timeout = time.time() + 5   # 5 second from now

buff = []

while True:
    buff.append(ser.readline())
    if time.time() > timeout:
        break

for e in buff:
    print e


print len(buff)
