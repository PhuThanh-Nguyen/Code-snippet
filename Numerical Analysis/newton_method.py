import warnings
from math import sin, cos, e

class NewtonMethod:
	
	def __init__(self, p0, f, f_deriv, tol = 1e-3, max_iter = 1000):
		self.p0, self.f, self.f_deriv, self.tol, self.max_iter = p0, f, f_deriv, tol, max_iter
	
	def fit(self):
		self.sequence, self.num_iter, self.actual_tol, self.solution = [self.p0,], 0, None, self.p0
		isConvergence = False
		p0 = self.p0
		
		for i in range(self.max_iter):
			p = p0 - self.f(p0)/self.f_deriv(p0)
			self.sequence.append(p)
		
			if (abs(p - p0) < self.tol) or abs(self.f(p)) < self.tol:
				self.num_iter, self.actual_tol = i, max(abs(p - p0), abs(self.f(p)))
				self.solution = p
				isConvergence = True
				break
			p0 = p
		
		if not isConvergence:
			warnings.warn('Convergence warning: p is not in the range of tolerance yet')
			self.num_iter, self.actual_tol, self.solution = self.max_iter, max(abs(p - p0), abs(self.f(p))), p0
		
		self.info = {'Initial p0': self.p0, 'Initial tolerance': self.tol, 'Max iteration': self.max_iter,\
			'Sequence': self.sequence, 'Iteration numbers' :  self.num_iter,\
			'Actual tolerance': self.actual_tol, 'Solution': self.solution}
		return self
	
	def __str__(self):
		return "Newton Method({})".format([str(key) + '=' + str(value) for (key, value) in self.info.items()])
	
	def convergence_info(self):
		return self.info

def f(x):
	return e**x - sin(x)

def f_deriv(x):
	return e**x - cos(x)

def main():
	p = NewtonMethod(1, f, f_deriv, 1e-6, 1000)
	p.fit()
	print(p.solution)
	print(p)

if __name__ == '__main__':
	main()
