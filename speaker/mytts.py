#!/usr/bin/python
# -*- coding: UTF-8 -*-
from gtts import gTTS
import os
# tts = gTTS(text='', lang='zh-tw')
# tts = gTTS(text='徐沐多,我又回来了! 你想不想我呀? 你又在玩麻将呀, 我们来做好朋友吧. ', lang='zh-tw')
# tts.save("hello.mp3")
# os.system("mplayer hello.mp3")

def speaker(str):
    tts = gTTS(text=str, lang='zh-tw')
    tts.save("hello.mp3")
    os.system("mplayer hello.mp3")


#speaker("你们怎么又开始打麻将了, 打麻将是赌博呀!")
