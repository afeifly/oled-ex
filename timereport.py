#!/usr/bin/env python
# -*- coding: utf-8 -*-
import restclient
import datetime
import time
def getCurrentTime():
#    theTime = datetime.datetime.now()
    localtime = time.localtime()
    theTime = time.strftime("%H点", localtime) 
    print(theTime)
    return theTime;

if __name__ == '__main__':
    msg = '滴---滴!!!! 现在时刻'+getCurrentTime()+'整!'
    restclient.send(msg)
