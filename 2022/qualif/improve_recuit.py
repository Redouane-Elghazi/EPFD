import IO_hashcode as io
import scoring
import random
import math

contributors, c2S, projects, p2D, p2W, p2B, p2S = io.read_input_file("input/e.txt")
p_order, p2C_order = io.read_output_init_file("output/optim8.out", projects, contributors)

P = len(p_order)
score = scoring.score(contributors, c2S, projects, p2D, p2W, p2B, p2S, p_order, p2C_order)

save_step = 100000
last_save = score
nb_save = 0

max_nb_test = 1000
nb_test = 0
a = 1 / 10000000000

print(score)
swaps = 0
max_swaps = 10000
while nb_test < max_nb_test and swaps < max_swaps:
	if score - last_save > save_step:
		print("Saving")
		io.write_output("output/optim{}.out".format(nb_save), projects, contributors, p_order, p2C_order)
		nb_save += 1
		last_save = score

	temp = 1 - (swaps+1/max_swaps)
	nb_test += 1
	p1 = random.randint(0, P-1)
	p2 = random.randint(0, P-2)
	if p2 >= p1:
		p2 += 1
	p_order[p1], p_order[p2] = p_order[p2], p_order[p1]
	p2C_order[p1], p2C_order[p2] = p2C_order[p2], p2C_order[p1]
	if not scoring.verif(contributors, c2S, projects, p2D, p2W, p2B, p2S, p_order, p2C_order):
		p_order[p1], p_order[p2] = p_order[p2], p_order[p1]
		p2C_order[p1], p2C_order[p2] = p2C_order[p2], p2C_order[p1]
		print("nul")
	else:
		new_score = scoring.score(contributors, c2S, projects, p2D, p2W, p2B, p2S, p_order, p2C_order)
		if new_score < score:
			if math.exp(- a * (score - new_score) / temp) < random.random():
				p_order[p1], p_order[p2] = p_order[p2], p_order[p1]
				p2C_order[p1], p2C_order[p2] = p2C_order[p2], p2C_order[p1]
			else:
				print(math.exp(- a * (score - new_score) / temp))
				print(- a * (score - new_score) / temp)
				swaps += 1
				nb_test = 0
				print(new_score)
				score = new_score
		elif new_score > score:
			swaps += 1
			nb_test = 0
			print(new_score)
			score = new_score

print("Saving")
io.write_output("output/optim{}.out".format(nb_save), projects, contributors, p_order, p2C_order)
nb_save += 1
last_save = score

@exit
def save():
	print("Saving")
	io.write_output("output/optim{}.out".format(nb_save), projects, contributors, p_order, p2C_order)