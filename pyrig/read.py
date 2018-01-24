import serial
ser = serial.Serial('/dev/cu.usbmodem1441', 115200)

x0 = 0
x1 = 0
buff = [[[], []], [[], []]]

datapoints = 6000
'''
buff is essentially the data on y axis

buff[0][0]
buff[0][1]
buff[1][0]
buff[1][1]

Time is x axis
'''
time = [0]
while True:
    temp = ser.readline()
    """z = '0'
    for i in range(len(temp)):
        if temp[i] <= '9' and temp[i] >= '0':
            z = z + temp[i]
            if len(z) > 3:
                z = '80'
                break
        else:
            break"""
    buff[x0][x1].append(int('0'+temp[:-2]))
    x1 = x1 ^ x0
    x0 = x0 ^ 1
    #print '~~~', , z
    if not x0 and not x1:
        time.append(time[-1]+1)
    if time[-1] > datapoints:
        time = time[:-1]
        break

print len(time), len(buff[0][0]), len(buff[0][1]), len(buff[1][0]), len(buff[1][1])

import numpy as np
import matplotlib.pyplot as plt

# evenly sampled time at 200ms intervals

# red dashes, blue squares and green triangles
plt.plot(time, buff[0][0], 'r', time, buff[0][1], 'b', time, buff[1][0], 'g', time, buff[1][1], 'y')
plt.axis([0, datapoints, 50, 150])
plt.show()
