import warnings

def fixedPointIteration(g, p0, tol = 1e-3, max_iter = 1000):
	for i in range(max_iter):
		p = g(p0)
		if abs(p - p0) < tol:
			return p
		p0 = p
	warnings.warn('Convergence warning: p is not in the range of tolerance yet')
	return p

def solveFunc(f, p0, tol = 1e-3, max_iter = 1000):
	def g(x):
		return f(x) + x
	return fixedPointIteration(g, p0, tol, max_iter)

def f(x):
	return 3**(-x) - x

def main():
	p = solveFunc(f, 1, 1e-5, max_iter = 10**6)
	print(p, f(p))

if __name__ == '__main__':
	main()
