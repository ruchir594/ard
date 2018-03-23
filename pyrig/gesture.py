#!/usr/bin/env python

from descent import Descent
from collections import Counter

class Gesture(object):

    def __init__(self):
        self.m = 0
        self.y = []
        self.obj = Descent()

    def clearobj(self):
        self.m = 0
        self.y = []
        
    def gd(self, data, threshold, control=5):
        i=0
        temp=-1
        y=[]

        while i < len(data)-1:
            temp = self.obj.gradient_descent(data[i], threshold)
            while temp == -1 and i < len(data)-1:
                i+=1
                temp = self.obj.gradient_descent(data[i], threshold)

            w=[]
            temp = self.obj.gradient_descent(data[i], threshold)
            while temp != -1 and i < len(data)-1:
                w.append(temp)
                i+=1
                temp = self.obj.gradient_descent(data[i], threshold)

            # now w has one chunk
            cnt = 0
            for j in range(1, len(w)):
                if w[j] > w[j-1]:
                    cnt += 1
                elif w[j] < w[j-1]:
                    cnt -= 1
            #print i, cnt
            if cnt > control:
                y.append(2)
            elif cnt < -control:
                y.append(1)
        return y

    def gd_double_touch(self, data, threshold, control=0):
        i=0
        temp1 = -1
        temp2 = -1
        y=[]

        last_i = -1;

        while i < len(data)-1:
            temp1 = self.obj.gradient_descent(data[i], threshold)
            temp2 = self.obj.gradient_descent(data[i][::-1], threshold)
            while temp1 == -1 and i < len(data)-1:
                i+=1
                temp1 = self.obj.gradient_descent(data[i], threshold)
                temp2 = self.obj.gradient_descent(data[i][::-1], threshold)

            w1=[]
            w2=[]
            temp1 = self.obj.gradient_descent(data[i], threshold)
            temp2 = self.obj.gradient_descent(data[i][::-1], threshold)
            while temp1 != -1 and i < len(data)-1:
                w1.append(temp1)
                w2.append(15-temp2)
                i+=1
                temp1 = self.obj.gradient_descent(data[i], threshold)
                temp2 = self.obj.gradient_descent(data[i][::-1], threshold)

            # now w has one chunk
            print len(w1), len(w2), w1, w2

            if len(w1) > 2:
                if w1 == w2:
                    if i-last_i < 20:
                        y.pop()
                        y.append('d_'+str(max(k for k,v in Counter(w1).items() if v>1)))
                    else:
                        y.append(max(w1))
                else:
                    if y and i-last_i < 20:
                        y.pop()
                    y.append('m_'+str(max(k for k,v in Counter(w1).items() if v>1))+'_'+str(max(k for k,v in Counter(w2).items() if v>1)))

            last_i = i
        return y
