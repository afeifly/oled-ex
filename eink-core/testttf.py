# -*- coding: utf-8 -*-
import pygame
import cv2
pygame.init()

def F16X16(chinese):
    font = pygame.font.Font("msyh.ttf",30)
    rtext = font.render(chinese, 0, (0, 0, 0), (255, 255, 255))
    pygame.image.save(rtext, 'pic/'+chinese+'.jpg')
    temp=cv2.imread('pic/'+chinese+'.jpg',cv2.IMREAD_GRAYSCALE)
    str=''
    str+='0x00,0x00,'#补两列空格
    for col in range(13):
        out=0
        for row in range(8):
            if temp[row][col]<50:#黑色
                out=out+pow(2,row)
        str=str+hex(out)+','
    str+='0x00,\n0x00,0x00,'
    for col in range(13):
        out=0
        for row in range(8):
            if temp[row+8][col]<50:
                out=out+pow(2,row)
        str=str+hex(out)+','
    str+='0x00,'
    print(str,'//',chinese)
chinese=u'博客你好123abcAD'
for ch in chinese:
    F16X16(ch)

