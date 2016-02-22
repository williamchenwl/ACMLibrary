# -*- coding: utf-8 -*-
import os
filename = os.listdir()
header_file = open("header.txt")
header = header_file.read()
for s in filename:
		if (s == 'headeradd.py') : continue
		if (s == 'header.txt') : continue
		w = open(s)
		content = w.read()
		w = open(s,'w')
		w.write(header)
		w.write(content)
