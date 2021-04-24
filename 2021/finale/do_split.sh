#python3 main2.py < input/constrained_optimisation.txt > output/c.txt
#python3 main2.py < input/distinction.txt > output/d.txt
#python3 main2.py < input/expectation_maximisation.txt > output/e.txt
#python3 main2.py < input/five_thousand.txt > output/f.txt

for i in $(seq 10 1000 200)
do
	python3 main2.py ${i} < input/constrained_optimisation.txt > output/c_${i}.txt
	k=$(python3 simulator.py input/constrained_optimisation.txt output/c_${i}.txt)
	echo ${k}
	python3 main2.py ${i} < input/distinction.txt > output/d_${i}.txt
	python3 main2.py  ${i}< input/expectation_maximisation.txt > output/e_${i}.txt
	python3 main2.py  ${i} < input/five_thousand.txt > output/f_${i}.txt
done