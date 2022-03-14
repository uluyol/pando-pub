#!/usr/bin/env python3

from typing import List

_MAX_LINE_LEN = 510

def write_constraints(fout, constraints: List[str]):
	constraints.sort()
	fout.write("\nSUBJECT TO\n")
	for c in constraints:
		if len(c)+2 < _MAX_LINE_LEN:
			fout.write("\t")
			fout.write(c)
			fout.write("\n")
			continue
		fields = c.split()
		accum = [] # type: List[str]
		accum_len = 0
		for f in fields:
			if accum_len + len(f) + 2 > _MAX_LINE_LEN:
				fout.write("\t")
				fout.write(" ".join(accum))
				fout.write("\n")
				accum = []
				accum_len = 0
			accum.append(f)
			accum_len += len(f) + 1
		if accum_len > 0:
			fout.write("\t")
			fout.write(" ".join(accum))
			fout.write("\n")
			accum = []
			accum_len = 0
