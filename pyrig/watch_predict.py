from descent import Descent
from watch_gesture import WatchGesture

for i in range(3, 10):

    # read from file

    with open('../data/Data/0'+str(i)+'/watch/raw_4_0_unsync.txt') as f:
        x = f.readlines()

    with open('../data/Data/10/watch/raw_1_0_unsync.txt') as f:
        x = f.readlines()

    data=[]
    for e in x:
        data.append(map(float, e[:-1].split(' ')[1:-1]))

    #print len(data), len(data[0]), data[0]

    # --- get a gesture chunk ---



    d_obj = Descent()
    g_obj = WatchGesture()

    swipe_threshold = int(d_obj.median(data[0]))*0.80
    touch_threshold = int(d_obj.median(data[0]))*0.10

    #swipe_threshold, touch_threshold = d_obj.auto_thresh(data)


    y = g_obj.gd(data, swipe_threshold, 1)
    if len(y)>3:
        print '~~~~\nSwipe Detected, Swipe gesture direction\n'
        print len(y), y
