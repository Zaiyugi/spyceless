def add(x, y):
	z = x + y
	return z
end

def sub(x, y):
	z = x - y
	return z
end

def main():
	x = add(0,1.0)
	y = sub(2.1,3.2)
	sub(4.3,5.4)
	z = add(sub(6.7, 7.8), sub(8.9, 9))
end
