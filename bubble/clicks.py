n, b = map(int, input().split())
while n+b!=0:
	s = ""
	while n!=0:
		i = n%b
		n = n//b
		s += "S"*i
		if n==1 and b==2:
			n = 0
			s+= "SS"
		elif n!=0:
			s += "M"
	print(len(s), s[::-1])
	n, b = map(int, input().split())
