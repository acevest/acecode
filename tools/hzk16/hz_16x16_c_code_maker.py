#!/usr/bin/python
#encoding: utf-8
import sys
import binascii

RECT_HEIGHT = 16
RECT_WIDTH = 16
BYTE_COUNT_PER_ROW = RECT_WIDTH / 8
BYTE_COUNT_PER_FONT = BYTE_COUNT_PER_ROW * RECT_HEIGHT

KEYS = [0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01]

class FontRender(object):
    def __init__(self, font_file,
                 rect_height=RECT_HEIGHT, rect_width=RECT_WIDTH, byte_count_per_row=BYTE_COUNT_PER_ROW):
        self.font_file = font_file
        self.rect_height = rect_height
        self.rect_width = rect_width
        self.byte_count_per_row = byte_count_per_row

        self.__init_rect_list__()

        self.c_code_list = []

    def __init_rect_list__(self):
        self.rect_list = [] * RECT_HEIGHT

        for i in range(RECT_HEIGHT):
            self.rect_list.append([] * RECT_WIDTH)

    def get_font_area_index(self, txt, encoding='utf-8'):
        if not isinstance(txt, unicode):
            txt = txt.decode(encoding)

        gb2312 = txt.encode('gb2312')
        hex_str = binascii.b2a_hex(gb2312)

        area = eval('0x' + hex_str[:2]) - 0xA0
        index = eval('0x' + hex_str[2:]) - 0xA0

        return area, index

    def get_font_rect(self, area, index):
        offset = (94 * (area-1) + (index-1)) * BYTE_COUNT_PER_FONT
        btxt = None

        with open(self.font_file, "rb") as f:
            f.seek(offset)
            btxt = f.read(BYTE_COUNT_PER_FONT)

        return btxt

    def convert_font_rect(self, font_rect):
        for k in range(len(font_rect) / self.byte_count_per_row):
            row_list = self.rect_list[k]
            for j in range(self.byte_count_per_row):
                for i in range(8):
                    asc = binascii.b2a_hex(font_rect[k * self.byte_count_per_row + j])
                    asc = eval('0x' + asc)
                    flag = asc & KEYS[i]
                    row_list.append(flag)

    def make_c_code(self, font_rect, ch) :
        c_code_str = '\n    // {0}\n'.format(ch)
        c_code_str += '    {'
        for k in range(len(font_rect) / self.byte_count_per_row):
            row_list = self.rect_list[k]
            for j in range(self.byte_count_per_row):
                data = 0
                for i in range(8):
                    asc = binascii.b2a_hex(font_rect[k * self.byte_count_per_row + j])
                    asc = eval('0x' + asc)
                    flag = asc & KEYS[i]
                    data <<= 1
                    if flag != 0 :
                        data |= 1

                if k != 0 or j != 0 :
                    c_code_str= c_code_str + ','
                c_code_str= c_code_str + str(hex(data))


        c_code_str += '}'
        self.c_code_list.append(c_code_str)



    def render_font_rect(self, rect_list=None):
        if not rect_list:
            rect_list = self.rect_list

        for row in rect_list:
            for i in row:
                if i:
                    print '■',
                else:
                    print '○',
            print

    def print_c_code(self) :
        s = 'const uint8_t PROGMEM chinese_str[][{0}] = '.format(BYTE_COUNT_PER_FONT)
        s += '{'
        for i in range(0, len(self.c_code_list)) :
            if i != 0 :
                s += ','
            s += self.c_code_list[i]

        s += '\n};'

        print(s)


    def convert(self, text, encoding='utf-8'):
        if not isinstance(text, unicode):
            text = text.decode(encoding)

        for t in text:
            area, index = self.get_font_area_index(t)
            font_rect = self.get_font_rect(area, index)

            self.make_c_code(font_rect, t.encode(encoding))
            self.convert_font_rect(font_rect)

    def get_rect_info(self):
        return self.rect_list

if '__main__' == __name__:
    text = u''
    if len(sys.argv) != 2 :
        print("Usage:\n    {0} <string>".format(sys.argv[0]))
    text = sys.argv[1]
    fr = FontRender('./hzk16s')
    fr.convert(text)
    # print fr.get_rect_info()
    # fr.render_font_rect()
    fr.print_c_code()

