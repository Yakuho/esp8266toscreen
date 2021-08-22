import cv2

FORMAT = """#include "imagedata.h"
#include <avr/pgmspace.h>


unsigned char IMAGE_DATA[] PROGMEM = {
"""
NEW_LINE = 13


def convert(path, rot):
    global FORMAT
    global NEW_LINE

    imageGray = cv2.cvtColor(cv2.imread(path), cv2.COLOR_RGB2GRAY)
    threshold, image01 = cv2.threshold(imageGray, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_TRIANGLE)
    vectors = (image01 // 255).flatten()
    # 坐标轴变换
    map_vectors = list()
    if rot == 0:
        for i in range(212):
            for j in range(104):
                map_vectors.append(vectors[104 * (211 - i) + j])
    elif rot == 1:
        for i in range(212):
            for j in range(104):
                map_vectors.append(vectors[212 * (103 - j) + (211 - i)])
    elif rot == 2:
        for i in range(212):
            for j in range(104):
                map_vectors.append(vectors[104 * i + (103 - j)])
    elif rot == 3:
        for i in range(212):
            for j in range(104):
                map_vectors.append(vectors[212 * j + i])
    # 取模
    for i in range(len(map_vectors) // 8):
        value = '0b'
        for bit in map_vectors[i * 8: (i + 1) * 8]:
            value += str(bit)
        else:
            FORMAT += f'0x{hex(eval(value))[2:]:0>2}, '
        if (i + 1) % NEW_LINE == 0:
            FORMAT += '\n'
    else:
        FORMAT += "};"

    print(FORMAT)


if __name__ == "__main__":
    convert(path="../docs/demo1.png", rot=3)
