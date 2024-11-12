import numpy as np

fair = np.array([1/6]*6)
load = np.array([0.15, 0.15, 0.2, 0.2, 0.15, 0.15])
convolved = np.convolve(fair, load)
print(convolved)
rolls_squared = np.arange(2,13)**2
ev_squared = np.dot(rolls_squared, convolved)
print(ev_squared)