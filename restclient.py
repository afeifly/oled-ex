#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import time
import requests
import json
from requests import post
from datetime import datetime
if os.name != 'posix':
    sys.exit('{} platform not supported'.format(os.name))
from PIL import ImageFont

def speak(msg):
    print('xxxx = '+msg)
   # task = '{"entity_id":"miio_acpartner.xmgw","message":"'+msg+'"}'
    task = {
                'entity_id' : 'miio_acpartner.xmgw',
                'message' : msg
            }
    print(json.dumps(task))
    headers = {
            'content-type': 'application/json', 
            'Authorization':'Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJleHAiOjE4NjQwMzAwNzgsImlzcyI6ImUwOGY2YWQyMzk3YzQ0YTc4YTIxMzYwZjhhMDJkZjdiIiwiaWF0IjoxNTQ4NjcwMDc4fQ.TfeI8Nk-82tqCWJvyQXlwMpTsOPolBTq1sVAXctfZzo'}
    #resp = requests.post('http://192.168.1.96:8123/api/services/miio_acpartner/play_tts',json=json.dumps(task),headers=headers)
    url = "http://192.168.1.96:8123/api/services/miio_acpartner/play_tts"
    response = post(url,headers=headers,data=json.dumps(task))
    print(response.text)

def send(msg):
    if msg=="kill":
        pass
        return
    speak(msg)
if __name__ == "__main__":
    try:
        send("徐陌阡 作业做完了没呀?")
    except KeyboardInterrupt:   # ctrl+c退出
        pass
