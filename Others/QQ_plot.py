import numpy as np
from matplotlib import pyplot as plt
from scipy.stats import norm as Normal, chi2 as ChiSquare

def QQ_plot(obsv):

	'''
		Construct Q-Q plot.
		---------------------------
		Parameters:
			obsv: 1-D list-like
				List of observations
		---------------------------
		Returns: Correlation coefficient r
			Display Q-Q plot
	'''
	
	observations = np.array(obsv)
	probability_levels = (observations.argsort() + 1/2)/observations.shape
	quantiles = Normal.ppf(probability_levels)
	
	quantiles.sort()
	observations.sort()
	
	fig, ax = plt.subplots()
	ax.scatter(quantiles, observations)
	plt.show()
	
	return np.corrcoef(observations, quantiles)[0,1]
