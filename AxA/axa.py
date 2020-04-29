import json
testcase = 1
infn = "ctstfr0244_input_" + str(testcase) + ".json"
outfn = "case" + str(testcase) + ".json"

with open(infn, "r") as f:
	IN = json.load(f)

OUT = [{"name":	w, "morningOptionIndex": 0, "eveningOptionIndex": 0} for w in IN["workers"]]

with open(outfn, 'w') as f:
	json.dump(OUT, f)