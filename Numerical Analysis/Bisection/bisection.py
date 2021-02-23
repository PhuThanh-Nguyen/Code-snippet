from math import log2, sqrt, cos, sin

def bisectionMethod(f, start, end, tol = 1e-3, max_iter = None, verbose = False):
	'''
		Perform bisection search
		Params:
			f: one variable real function
				Function f in equation `f(x) = 0 `
			start, end: floats
				Endpoints, `start` and `end` endpoints must satisfy f(start) * f(end) <= 0 in order to bisection method to work
			tol: float, default 1e-3
				Tolerance. Find solution p such that |f(p)| < tol
				If not specified but max_iter is given then tol will be calculated via parameter max_iter
			max_iter:  int, default None
				Upper bound number of iterations. If max_iter is None then max_iter will be calculated via parameter tol
				max_iter and tol are related by inequality (assume f is differentiable continuous on [start, end] and f(start)f(end) < 0)
						|p_n - p| < (end - start)/2**max_iter <= tol
			verbose: bool, default False
				If True, print out `a_n`, `b_n`, and `p_n` at each iteration
		Returns:
			Solution p such that |f(p)| < tol
			If solution p doesn't meet that condition, a warning will be raise
			A solution that doesn't meet condition only because floating number calculation
	'''
	if f(start) * f(end) > 0:
		raise ValueError('Function at starting point and ending point must have different sign')
	if max_iter is None:
		max_iter = int(log2((end - start)/tol)) + 1
	else:
		tol = (end - start)/(2**max_iter)
	FA = f(start)
	for i in range(max_iter + 1):
		p = start + (end - start)/2
		FP = f(p)
		if verbose:
			print(f'a_{i} = {start} \t b_{i} = {end} \t p_{i} = {p}')
		if abs(FP) < tol or (end - start) < tol:
			return p
		if (FA * FP) > 0:
			start = p
			FA = FP
		else:
			end = p
	raise Warning('Convergence warning: p is not in the range of tolerance yet')
	return p

def f(x):
	return sin(x)

def main():
	p = bisectionMethod(f, 2, 4, tol = 1e-6)
	print(p)

if __name__ == '__main__':
	main()
