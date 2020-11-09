
def fixedPointIteration(g, p0, tol, max_iter):
	for i in range(max_iter):
		p = g(p0)
		if abs(p - p0) < tol:
			return p
		p0 = p
	raise Warning('Convergence warning: p is not in the range of tolerance yet')
	return p

def f(x):
	return 

def main():
	pass

if __name__ == '__main__':
	main()
