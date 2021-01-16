import binascii
import base64
array = []
array.append('1')
array.append('2')
array.append('3')
print(array)
KEYS = [0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01]

def print2console(font_rect):
    rect_list = [] * 16
    for i in range(16):
        rect_list.append([] * 16)

    for k in range(len(font_rect) // 2):
        # 每行数据
        row_list = rect_list[k]
        for j in range(2):
            for i in range(8):
                asc = font_rect[k * 2 + j]
                # 此处&为Python中的按位与运算符
                flag = asc & KEYS[i]
                # 数据规则获取字模中数据添加到16行每行中16个位置处每个位置
                row_list.append(flag)

    line = '■'
    background = '○'
    for row in rect_list:
        for i in row:
            if i:
                # 前景字符（即用来表示汉字笔画的输出字符）
                print(line, end=' ')
            else:

                # 背景字符（即用来表示背景的输出字符）
                print(background, end=' ')
        print()
def print_hex(bytes):
    l = [hex(int(i)) for i in bytes]
def numsofone_in_charbytes(text):
    # 先获取字符的ascii码值
    offset = ord(text)
    # 然后打开字库文件找到位置
    with open("ASC16", "rb") as ASC16:
        location = offset*16
        ASC16.seek(location)
        retbytes = ASC16.read(16)
        return retbytes

def getEncodeHZK(textStr):
    array = []
    # 初始化16*16的点阵位置，每个汉字需要16*16=256个点来表示，需要32个字节才能显示一个汉字
    # 之所以32字节：256个点每个点是0或1，那么总共就是2的256次方，一个字节是2的8次方
    rect_list = [] * 16
    for i in range(16):
        rect_list.append([] * 16)
    for text in textStr:
        # 获取中文的gb2312编码，一个汉字是由2个字节编码组成
        gb2312 = text.encode('gb2312')
        # 将二进制编码数据转化为十六进制数据
        hex_str = binascii.b2a_hex(gb2312)
        # 将数据按unicode转化为字符串
        result = str(hex_str, encoding='utf-8')
        # 前两位对应汉字的第一个字节：区码，每一区记录94个字符
        area = eval('0x' + result[:2]) - 0xA0
        # 后两位对应汉字的第二个字节：位码，是汉字在其区的位置
        try:
            index = eval('0x' + result[2:]) - 0xA0
            offset = (94 * (area-1) + (index-1)) * 32
            font_rect = None
            print("read start")
            # 读取HZK16汉字库文件
            with open("HZK16", "rb") as f:
                # 找到目标汉字的偏移位置
                f.seek(offset)
                # 从该字模数据中读取32字节数据
                font_rect = f.read(32)
            print('font rect array 32 = ')
            print('1')
            print(font_rect)
            print('2')
            print(font_rect.decode('utf-8'))
            print('3')
            for i in font_rect:
                print('%#x'%ord(i)) 
            #print(font_rect.decode("utf-8"))
            print('4')
            #print_hex(font_rect.decode("utf-8"))
            encodeTxt = base64.b64encode(font_rect) 
            print(encodeTxt)

            # print2console(font_rect)
            array.append(encodeTxt.decode("utf-8"))
        except Exception as e:
            print('EEEEEEEEE:::::')
            waxx = numsofone_in_charbytes(text)
            print(waxx)
            print2console(numsofone_in_charbytes(text))
            encodeTxt = base64.b64encode(numsofone_in_charbytes(text)) 
            array.append(encodeTxt.decode("utf-8"))
        # 汉字在HZK16中的绝对偏移位置，最后乘32是因为字库中的每个汉字字模都需要32字节
        
    return array

array = getEncodeHZK('你A你')
print(array)
