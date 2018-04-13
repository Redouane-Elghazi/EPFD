from fractions import *

def gcd(a, b):
	if a==0:
		return b
	else:
		return gcd(b%a, a)

T = int(input())
for t in range(T):
	a, b = map(int, input().split('/'))
	x=Fraction(a,b)
	x = x.limit_denominator(b-1)
	print(str(x.numerator) + "/" + str(x.denominator))