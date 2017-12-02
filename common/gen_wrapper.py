#!/usr/bin/python
# -*- coding: utf-8 -*-

import re 

outname = "wrapper.cpp"
infile = open("comm.h", "r")
outfile = open(outname, "w")
contents = []
contents.append('#include "comm.h"')
body = """
{
	{} ret = {}({});
	if({}){{
		err_quit("call failed {}(%s:%d): %s.", __FILE__, __LINE__, strerror(errno));
	}
	return ret;
}
"""

bodylist = []
for line in body.split("\n"):
	line = line.strip("\r\n")
	if line:
		bodylist.append(line)

genstart = False
for line in infile.readlines():
	if line.find("/*gen_start*/") != -1:
		genstart = True

	if not genstart:
		continue

	line = line.strip()
	if (not line) or (line[0] in "/"):
		continue

	if line.find("#ifdef") != -1 or line.find("#endif") != -1:
		contents.append("")
		contents.append(line)
		continue

	line = line.replace(";", "").strip()
	left = line[0:line.find('(')]
	leftw = left.split()
	t = " ".join(leftw[0:-1])
	func = leftw[-1].lower()
	right = line[line.find('(') + 1:line.find(')')]
	rightw = right.split(",")
	param = [r.split()[-1].replace("*", "").replace("&","") for r in rightw if r.strip() !="void" ]

	condition = "ret < 0"
	m = re.search(r'/\*cond:\(([^)]+)\)\*/', line)
	if m:
		condition = m.group(1)

	contents.append("")
	contents.append(line)
	for index, bodyline in enumerate(bodylist):
		style = ()
		if index == 1:
			style = (t, func, ", ".join(param))
		elif index == 2:
			style = (condition,)
		elif index == 3:
			style = (func,)
		contents.append(bodyline.format(*style) if style else bodyline)

contents.append("")
outfile.write("\n".join(contents))

infile.close()
outfile.close()

print "gen {} finish".format(outname)
