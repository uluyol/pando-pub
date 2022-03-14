#!/usr/bin/env python3

from typing import Dict, Iterable, List, Tuple

MAX_LATENCY = 1000000

class Latency(object):
	def __init__(self, dcs: List[int], percentiles: List[str], latency_mat_path: str) -> None:
		self.get = {} # type: Dict[str, Dict[Tuple[int, int], float]]
		self.put = {} # type: Dict[str, Dict[Tuple[int, int], float]]

		for k in percentiles:
			self.get[k] = {}
			self.put[k] = {}
			for i in dcs:
				for j in dcs:
					self.get[k][(i, j)] = MAX_LATENCY
					self.put[k][(i, j)] = MAX_LATENCY

		with open(latency_mat_path) as fin:
			for line in fin:
				items = line.strip().split()
				dc_i = int(items[0])
				dc_j = int(items[1])
				if dc_i in dcs and dc_j in dcs:
					kind = items[2]
					pct = items[3]
					val = float(items[4])
					if pct not in percentiles:
						continue
					if kind == "GET":
						self.get[pct][(dc_i, dc_j)] = val
					elif kind == "PUT":
						self.put[pct][(dc_i, dc_j)] = val
					else:
						raise ValueError

	def sym_max(self, pct: str, a: str, b: str) -> float:
		ai = int(a)
		bi = int(b)
		gab = self.get[pct][(ai, bi)]
		gba = self.get[pct][(bi, ai)]
		pab = self.put[pct][(ai, bi)]
		pba = self.put[pct][(bi, ai)]
		return max(gab, gba, pab, pba)

	def sym_min(self, pct: str, a: str, b: str) -> float:
		ai = int(a)
		bi = int(b)
		gab = self.get[pct][(ai, bi)]
		gba = self.get[pct][(bi, ai)]
		pab = self.put[pct][(ai, bi)]
		pba = self.put[pct][(bi, ai)]
		return min(gab, gba, pab, pba)

def access_set_fes(p: str) -> Iterable[int]:
	with open(p) as fin:
		for line in fin:
			line = line.strip()
			if line and line[0] == "#":
				continue
			yield int(line)
