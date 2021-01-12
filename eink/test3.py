import binascii

KEYS = [0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01]

#初始化16*16的點陣位置，每個漢字需要16*16=256個點來表示
rect_list = [] * 16
for i in range(16):
    rect_list.append([] * 16)
#拿“贊”字來演示
text = "你"
#獲取中文的編碼
#gb2312 = text.encode('gb2312')
gb2312 = text.encode('gbk')
hex_str = binascii.b2a_hex(gb2312)
result = str(hex_str, encoding='utf-8')
#根據編碼計算“贊”在漢字庫中的位置
area = eval('0x' + result[:2]) - 0xA0
index = eval('0x' + result[2:]) - 0xA0
offset = (94 * (area-1) + (index-1)) * 32
font_rect = None
#讀取HZK16漢字庫文件中“贊”字數據
with open("HZK16", "rb") as f:
    f.seek(offset)
    font_rect = f.read(32)
#根據讀取到HZK中數據給我們的16*16點陣賦值
for k in range(len(font_rect) // 2):
    row_list = rect_list[k]
    for j in range(2):
        for i in range(8):
            asc = font_rect[k * 2 + j]
            flag = asc & KEYS[i]
            row_list.append(flag)
print('value now::::')
print(rect_list)
#根據獲取到的16*16點陣信息，打印到控制檯
for row in rect_list:
    for i in row:
        if i:
#前景字符（即用來表示漢字筆畫的輸出字符）
            print('0', end=' ')
        else:
#背景字符（即用來表示背景的輸出字符）
            print('.', end=' ')
    print()
