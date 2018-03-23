#!/usr/bin/env python

class Descent(object):

    def __init__(self):
        # does nothing
        self.m = 0

    def gradient_descent(self, a, threshold):
        # returns -1 if no lowest point below threshold
        # else returns index of lowest element
        for i in range(len(a)):
            if a[i] < threshold:
                j=i+1
                while j<len(a) and a[j] < a[j-1]:
                    j=j+1
                return j-1
        return -1

    def median(self, a):
        a.sort()
        return a[len(a)/2]

    def auto_thresh(self, a):
        b=[]
        for e in a:
            b.extend(e)
        b.sort()
        print len(b), b[1000], b[len(b)/2]
        return b[len(b)/2]*0.85, b[len(b)/2]*0.10
