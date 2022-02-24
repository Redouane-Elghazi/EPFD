from typing import List, Dict, Tuple


def learning(p2S: List[Tuple[str, int]], p2C_order: List[int], c2S: List[Dict[str, int]]):
	n = len(p2S)
	for i in range(n):
		contrib = p2C_order[i]
		role = p2S[i]
		if c2S[contrib][role[0]] <= role[1]:
			c2S[contrib][role[0]] += 1


def find_contributor(p2S: List[Tuple[str, int]], c2S: List[Dict[str, int]], role: int, mentor=false, start=0):
	for i in range(start, len(c2S)):
		if mentor and c2S[i][p2S[role][0]] >= p2S[role][1] - 1:
			return i
		elif c2S[i][p2S[role][0]] >= p2S[role][1]:
			return i
	return None


def find_contributors(p2S: List[Tuple[str, int]], c2S: List[Dict[str, int]], role: int):
	no_mentor = [i for i in range(len(c2S)) if c2S[i][p2S[role][0]] >= p2S[role][1]]
	with_mentor = [i for i in range(len(c2S)) if c2S[i][p2S[role][0]] == p2S[role][1] - 1]

	return no_mentor, with_mentor


def find_contributors_yield(p2S: List[Tuple[str, int]], c2S: List[Dict[str, int]], role: int, mentor=false, start=0):
	for i in range(start, len(c2S)):
		if mentor and c2S[i][p2S[role][0]] >= p2S[role][1] - 1:
			yield i
		elif c2S[i][p2S[role][0]] >= p2S[role][1]:
			yield i
