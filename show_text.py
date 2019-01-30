#!/usr/bin/env python
# -*- coding: utf-8 -*-

import os
import sys
import time
from datetime import datetime
if os.name != 'posix':
    sys.exit('{} platform not supported'.format(os.name))
from demo_opts import get_device
from luma.core.render import canvas
from PIL import ImageFont

def show(device,msg):
    # use custom font
    #font_path = os.path.abspath(os.path.join(os.path.dirname(__file__),'fonts', 'code2000.ttf')) # 导入字体文件
    font_path = os.path.abspath(os.path.join(os.path.dirname(__file__),'fonts', 'NotoSansMonoCJKsc-Regular.otf')) # 导入字体文件
    font2 = ImageFont.truetype(font_path, 12)   #设置字体类型和字体大小
    lenght = 12;
    # 开始输出
    print('xxxx = '+msg)
    with canvas(device) as draw:
        # draw.text((x,y),"输出内容",font=字体,fill=颜色)
        # 这3行基本占满了128*64的oled屏幕
        strln = len(msg)
        print(strln)
        for row in range(0,4):
            start = 10*row
            end = start + 10
            if strln<start:
                break
            elif strln<end:
                draw.text((0, lenght*row+row), msg[start:strln], font=font2, fill="white")
            else:
                draw.text((0, lenght*row+row), msg[start:end], font=font2, fill="white")

def send(msg):
    # 如果不写在循环里，执行完程序就退出了，就看不到内容
    device = get_device()   # 获取并输出设备信息 demo_opts.get_device()
    #while True:
    if msg=="kill":
        pass
        return
    show(device,msg)
    time.sleep(10)
def kill():
    device = get_device()
    show(device)
if __name__ == "__main__":
    try:
   #     device = get_device()   # 获取并输出设备信息 demo_opts.get_device()
        send()
    except KeyboardInterrupt:   # ctrl+c退出
        pass
