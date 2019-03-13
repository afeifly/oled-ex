#!/usr/bin/env python
# -*- coding: utf-8 -*-
import restclient
import datetime
import time
def getCurrentTime():
#    theTime = datetime.datetime.now()
    localtime = time.localtime()
    theTime = time.strftime("%-H", localtime) 
    int_Time = int(theTime)
    if int_Time<=12 :
        theTime = "上午"+str(int_Time) 
    elif int_Time>12 and int_Time<19 :
        theTime = "下午"+str(int_Time-12) 
    else :
        theTime = "晚上"+str(int_Time-12) 
#    theTime = "上午"+str(int_Time) if int_Time<12 else "下午"+str(int_Time-12)
    return theTime;

if __name__ == '__main__':
    msg = '滴---滴!!!! 现在时刻'+getCurrentTime()+'点整!'
    restclient.send(msg)
