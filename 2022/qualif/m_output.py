def write_output(projects, contributors, projects_order, p2C_order):
    print(len(projects_order))
    for p, C in zip(projects_order, p2C_order):
        print(projects[p])
        for c in C:
            print(contributors[c])
