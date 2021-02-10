def Chi_Square_plot(obsv):
	
	'''
		Construct Chi-square plot.
		------------------------------
		Parameters:
			obsv: 2-D array
				List of observations, each row is an observation
		------------------------------
		Returns: None
			Display Chi Square plot
	'''
	
	observations = np.array(obsv)
	df = observations.shape[1]
	mean = observations.mean(axis = 0).reshape((df, 1))
	S_inv = np.linalg.inv(np.cov(observations, ddof = 1, rowvar = False))
	d = []
	for obs in observations:
		vec = obs.reshape((df, 1))
		d_j = (vec - mean).T.dot(S_inv).dot(vec - mean)[0,0]
		d.append(d_j)
	
	d = np.array(d)
	d.sort()
	
	probability_levels = (d.argsort() + 1/2)/d.shape
	
	quantiles = ChiSquare.ppf(probability_levels, df)
	
	fig, ax = plt.subplots()
	ax.scatter(quantiles, d)
	plt.show()
