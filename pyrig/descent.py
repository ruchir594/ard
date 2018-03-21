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
        return a[8]
