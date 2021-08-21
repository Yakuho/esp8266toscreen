import numpy
import cv2
FORMAT = """#include "imagedata.h"
#include <avr/pgmspace.h>


unsigned char IMAGE_DATA[] PROGMEM = {
"""
NEW_LINE = 16


def convert(path, rotage):
	global FORMAT
	global NEW_LINE
	imageBGR = cv2.imread(path)
	imageGray = cv2.cvtColor(imageBGR, cv2.COLOR_RGB2GRAY)
	threshold, image01 = cv2.threshold(imageGray, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_TRIANGLE)
	image01 = image01 // 255
	vetors = image01.flatten()
	
	map_vetors = list()
	cmap = numpy.array([1, 2, 4, 8, 16, 32, 64, 128])
	if rotage == 0:
		pass
	elif rotage == 1:
		pass
	elif rotage == 2:
		pass
	elif rotage == 3:
		for i in range(212):
			for j in range(104):
				map_vetors.append(vetors[212 * j + i])
	for i in range(len(map_vetors) // 8):
		FORMAT += f'0x{hex(numpy.sum(numpy.array(map_vetors[i*8: (i+1)*8]) * cmap))[2: ]:0>2}, '
		if (i + 1) % NEW_LINE == 0:
			FORMAT += '\n'
	else:
		FORMAT += "};"
	print(FORMAT)
		

if __name__ == "__main__":
	convert(path="a.png", rotage=3)
