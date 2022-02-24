import IO_hashcode as io
import scoring

contributors, c2S, projects, p2D, p2W, p2B, p2S = io.read_input("input/e.txt")
p_order, p2C_order = io.read_output("output/e.out", projects, contributors)
print(scoring.score(contributors, c2S, projects, p2D, p2W, p2B, p2S, p_order, p2C_order))
