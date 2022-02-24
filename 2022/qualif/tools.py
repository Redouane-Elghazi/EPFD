from typing import List, Dict, Tuple


# fait des copies
def learning(project: List[Tuple[str, int]], contributors: List[Dict[str, int]]) -> List[Dict[str, int]]:
	new_contributors = [d for d in contributors]
	n = len(project)
	for i in range(n):
		if contributors[i][project[0][i]] <= project[1][i]:
			new_contributors[i][project[1][i]] += 1
	return new_contributors


def find_contributors(project: List[Tuple[str, int]], contributors: List[Dict[str, int]], role: int):
	no_mentor = [i for i in range(len(contributors)) if contributors[i][project[role][0]] >= project[role][1]]
	with_mentor = [i for i in range(len(contributors)) if contributors[i][project[role][0]] == project[role][1]-1]

	return no_mentor, with_mentor
