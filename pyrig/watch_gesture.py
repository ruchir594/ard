#!/usr/bin/env python

from descent import Descent
from collections import Counter

class WatchGesture(object):

    def __init__(self):
        self.m = 0
        self.y = []
        self.obj = Descent()

    def clearobj(self):
        self.m = 0
        self.y = []

    def findLongestConseqSubseq(self, arr):

        # Time Complexity O(n) - Linear

        s = set([])
        ans=0
        sp=-1

        # Hash all the array elements
        for ele in arr:
            s.add(ele)

        # check each possible sequence from the start
        # then update optimal length
        for i in range(len(arr)):

             # if current element is the starting
            # element of a sequence
            if (arr[i]-1) not in s:

                # Then check for next elements in the
                # sequence
                j=arr[i]
                while(j in s):
                    j+=1

                # update  optimal length if this length
                # is more
                if j-arr[i] > ans:
                    ans = j-arr[i]
                    sp = arr[i]
                #ans=max(ans, j-arr[i])
        return ans, sp

    def gd(self, data, threshold, control=5):
        i=0
        temp=-1
        y=[]

        #print len(data), len(data[0]), data[0]

        tdata = []
        for e in data:
            tdata.append([e[:6], e[6:11], e[11:17], e[17:]])

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
            #print len(w), self.findLongestConseqSubseq(w)

            cnt = 0
            for j in range(1, len(w)):
                if w[j] > w[j-1]:
                    cnt += 1
                elif w[j] < w[j-1]:
                    cnt -= 1

            if len(w) > 3:
                a, b = self.findLongestConseqSubseq(w)
                if b + a/2 in range(0, 6) or b + a/2 in range(11,17):
                    if cnt > control:
                        y.append(2)
                    elif cnt < -control:
                        y.append(1)
                    #y.append('1/2')
                elif b + a/2 in range(6, 11) or b + a/2 in range(17, 22):
                    if cnt > control:
                        y.append(4)
                    elif cnt < -control:
                        y.append(3)
        return y
