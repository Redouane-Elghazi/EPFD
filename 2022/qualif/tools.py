from typing import List, Dict, Tuple


def learning(project: List[Tuple[str, int]], contributors: List[Dict[str, int]]) -> List[Dict[str, int]]:
	new_contributors = [d for d in contributors]
	n = len(project)
	for i in range(n):
		if contributors[i][project[0][i]] <= project[1][i]:
			new_contributors[i][project[1][i]] += 1
	return new_contributors


def find_contributor(project: List[Tuple[str, int]], contributors: List[Dict[str, int]], role: int, mentor: bool,
					 start: int):
	for i in range(start, len(contributors)):
		if mentor and contributors[i][project[role][0]] >= project[role][1] - 1:
			return i
		elif contributors[i][project[role][0]] >= project[role][1]:
			return i
	return None


def find_contributors(project: List[Tuple[str, int]], contributors: List[Dict[str, int]], role: int):
	no_mentor = [i for i in range(len(contributors)) if contributors[i][project[role][0]] >= project[role][1]]
	with_mentor = [i for i in range(len(contributors)) if contributors[i][project[role][0]] == project[role][1] - 1]

	return no_mentor, with_mentor


def find_contributors_yield(project: List[Tuple[str, int]], contributors: List[Dict[str, int]], role: int, mentor: bool,
							start=0):
	for i in range(start, len(contributors)):
		if mentor and contributors[i][project[role][0]] >= project[role][1] - 1:
			yield i
		elif contributors[i][project[role][0]] >= project[role][1]:
			yield i
