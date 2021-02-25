import json
from random import randint, seed
import mip

seed(4568181913454)
testcase = 3
timeout = 1200  # 20 minutes max
M = "morningOptions"
E = "eveningOptions"
D = "domain"
infn = "ctstfr0244_input_" + str(testcase) + ".json"
outfn = "case" + str(testcase) + ".json"

with open(infn, "r") as f:
    IN = json.load(f)
W = IN["workers"]
quotas = IN["quotas"]

m = mip.Model(sense=mip.MINIMIZE, solver_name=mip.GRB)
wbosse = {w: m.add_var(var_type=mip.BINARY) for w in W}  # Workers if working

# Constraints on quotas
for d in quotas:
    m += mip.xsum(wbosse[w] for w in W if W[w][D] == d) >= quotas[d]
    # print(quotas[d], [w for w in W if W[w][D] == d])

wtop_morn = {w: [m.add_var(var_type=mip.BINARY) for i in range(len(W[w][M]))] for w in
             W}  # Workers to set of paths on morning
wtop_even = {w: [m.add_var(var_type=mip.BINARY) for i in range(len(W[w][E]))] for w in
             W}  # Workers to set of paths on evening

# Workers working should go to/come back from work
for w in W:
    m += wbosse[w] <= mip.xsum(wtop_morn[w])
    m += wbosse[w] <= mip.xsum(wtop_even[w])

# Computing all transports possibles
all_transport = {w: [] for w in W}
for w in W:
    for path in W[w][M]:
        all_transport[w] += path
    for path in W[w][E]:
        all_transport[w] += path
all_transport = {w: list(set(all_transport[w])) for w in W}

wtot = {w: {t: m.add_var(var_type=mip.BINARY) for t in all_transport[w]} for w in W}  # Workers to set of transports

# Must take all transports along a path
for w in W:
    for i in range(len(W[w][M])):
        path = W[w][M][i]
        for t in path:
            m += wtot[w][t] >= wtop_morn[w][i]
    for i in range(len(W[w][E])):
        path = W[w][E][i]
        for t in path:
            m += wtot[w][t] >= wtop_even[w][i]

vision = {w: {w2: {t: m.add_var(var_type=mip.BINARY) for t in all_transport[w] if t in all_transport[w2]} for w2 in W if
              w != w2} for w in W}  # If two workers see each other on one transport

# Seeing each other means being on the same transport
list_triple = []
for w in W:
    for w2 in W:
        if w2 == w:
            continue
        for t in vision[w][w2]:
            m += vision[w][w2][t] >= -1 + wtot[w][t] + wtot[w2][t]  # (c)Tashiqi
            list_triple.append((w, w2, t))

m.objective = mip.minimize(mip.xsum(vision[w][w2][t] for (w, w2, t) in list_triple))

# m.write('model.lp')
# m.read('model.lp')
# print('model has {} vars, {} constraints and {} nzs'.format(m.num_cols, m.num_rows, m.num_nz))

print("Start")
m.optimize(max_seconds=timeout) 

res = {}
for w in W:
    # print(wbosse[w].x)
    if wbosse[w].x:
        ind_morn = [i for i in range(len(W[w][M])) if wtop_morn[w][i].x]
        # print(ind_morn)
        ind_even = [i for i in range(len(W[w][E])) if wtop_even[w][i].x]
        # print(ind_even)
        res[w] = ind_morn[0], ind_even[0]

OUT = [{"name": w, "morningOptionIndex": res[w][0], "eveningOptionIndex": res[w][1]} for w in res]
with open(outfn, 'w') as f:
    json.dump(OUT, f)
