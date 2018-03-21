# read from file

with open('../data/05/glasses/raw_7_0_unsync.txt') as f:
    x = f.readlines()

data=[]
for e in x:
    data.append(map(float, e[:-1].split(' ')[1:-1]))

#print len(data), len(data[0]), data[0]

# --- get a gesture chunk ---

from descent import Descent
from gesture import Gesture

d_obj = Descent()
g_obj = Gesture()

swipe_threshold = int(d_obj.median(data[0]))*0.75
touch_threshold = int(d_obj.median(data[0]))*0.10

y = g_obj.gd(data, swipe_threshold)
if len(y)>3:
    print '~~~~\nSwipe Detected, Swipe gesture direction\n'
    print len(y), y
else:
    y = g_obj.gd_double_touch(data, touch_threshold, 0)
    if y:
        print '~~~~\nTouch Detected, index of touch\n'
        print len(y), y
