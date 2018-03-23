from descent import Descent
from gesture import Gesture

#left
k1 = [458,  292,  1,    1,    204,  1,    37,   1]
k2 = [2871, 2963, 1515, 3237, 1894, 1562, 1932, 1669]

#right
#k1 = [155, 1, 1, 701, 121, 129, 1, 96]
#k2 = [2568, 2712, 2183, 3191, 1634, 2179, 2215, 1630]

for i in range(3, 10):

    # read from file

    with open('../data/Data/0'+str(i)+'/glasses/raw_1_0_unsync.txt') as f:
        x = f.readlines()

    data=[]
    for e in x:
        data.append(map(float, e[:-1].split(' ')[1:-1]))

    #print len(data), len(data[0]), data[0]

    # --- get a gesture chunk ---

    data = data[k1[i-3]-1:k2[i-3]]

    d_obj = Descent()
    g_obj = Gesture()

    swipe_threshold = int(d_obj.median(data[0]))*0.80
    touch_threshold = int(d_obj.median(data[0]))*0.10

    #swipe_threshold, touch_threshold = d_obj.auto_thresh(data)


    y = g_obj.gd(data, swipe_threshold, 2)
    if len(y)>3:
        print '~~~~\nSwipe Detected, Swipe gesture direction\n'
        print len(y), y
    else:
        y = g_obj.gd_double_touch(data, touch_threshold, 0)
        if y:
            print '~~~~\nTouch Detected, index of touch\n'
            print len(y), y

with open('../data/Data/10/glasses/raw_1_0_unsync.txt') as f:
    x = f.readlines()

data=[]
for e in x:
    data.append(map(float, e[:-1].split(' ')[1:-1]))

#print len(data), len(data[0]), data[0]

# --- get a gesture chunk ---

data = data[k1[-1]-1:k2[-1]]

d_obj = Descent()
g_obj = Gesture()

swipe_threshold = int(d_obj.median(data[0]))*0.80
touch_threshold = int(d_obj.median(data[0]))*0.10

#swipe_threshold, touch_threshold = d_obj.auto_thresh(data)


y = g_obj.gd(data, swipe_threshold, 2)
if len(y)>3:
    print '~~~~\nSwipe Detected, Swipe gesture direction\n'
    print len(y), y
else:
    y = g_obj.gd_double_touch(data, touch_threshold, 0)
    if y:
        print '~~~~\nTouch Detected, index of touch\n'
        print len(y), y
