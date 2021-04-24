def parse(filename):
    file = open(filename, "r")

    line = file.readline()
    temp = line.split(" ")
    L = int(temp[0])
    G = int(temp[1])
    S = int(temp[2])
    B = int(temp[3])
    F = int(temp[4])
    N = int(temp[5])

    # services
    services = {}
    for _ in range(S):
        line = file.readline()
        temp = line.split(" ")

        name = temp[0]
        binaries = int(temp[1])
        services[name] = binaries

    # features
    features = {}
    for _ in range(F):
        line = file.readline()
        temp = line.split(" ")

        name = temp[0]
        nb_services = int(temp[1])
        difficulty = int(temp[2])
        nb_users = int(temp[3])

        line = file.readline()
        temp = line.split(" ")

        s = [x.strip() for x in temp]
        for x in s:
            if x not in services:
                print(x, "WTF")
        features[name] = (nb_services, difficulty, nb_users, s)

    return L, G, S, B, F, N, services, features


def create_bin(B, services):
    binaries = [set() for i in range(B)]
    for k in services:
        binaries[services[k]].add(k)

    return binaries


def size_bins(binaries, B):
    return list(len(binaries[x]) for x in range(B))


def bins_per_features(features, services):
    flist = []
    for f in features:
        flist.append(set(services[s] for s in features[f][3]))

    tries = [{0}, {0, 1}, {1}]
    return [sum(1 for f in flist if f == t) for t in tries]



def score_for_features(L, end_impl, feat, features):
    return max(0, L - end_impl) * features[feat][2]


def minimum_end_impl(feat, features, services, binaries, B):
    diff = features[feat][1]
    sz_bins = size_bins(binaries, B)
    max_services = max(sz_bins[services[s]] for s in features[feat][3])
    return diff + max_services

def run():
    L, G, S, B, F, N, services, features = parse("expectation_maximisation.txt")
    BpF = bins_per_features(features, services)
    binaries = create_bin(B, services)

    flist = set(features.keys())
    order = []
    while flist:
        opt = None
        val = None
        for f in flist:
            chall_end = minimum_end_impl(f, features, services, binaries, B)
            chall_score = score_for_features(L - len(order), chall_end, f, features)
            if val is None or chall_score > val:
                opt = f
                val = chall_score
        order.append(opt)
        flist.remove(opt)

    nb_inge = B*F
    print(nb_inge)
    for f in order:
        for b in range(B):
            print(1)
            print("impl",f, b)



run()
