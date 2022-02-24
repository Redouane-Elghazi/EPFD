from typing import List, Dict, Tuple

def learning(project : List[Tuple[str, int]], contributors : List[Dict[str, int]]) -> List[Dict[str, int]]:
    new_contributors = [d for d in contributors]
    n = len(project)
    for i in range(n):
        if contributors[i][project[0][i]] <= project[1][i]:
            new_contributors[i][project[1][i]] += 1
    return new_contributors

def find_contributors(project, contributors, role):
    #list of contributors filling the role, list of contributors filling the role if mentor

