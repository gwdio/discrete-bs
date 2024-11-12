import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm
from scipy.special import factorial

# Define the sampling step size (0.01)
step_size = 0.01

# Define the range for sampling the Normal PDF and Poisson PMF from -2 to 8
x = np.arange(-2, 8, step_size)  # Sample normal and poisson over range (-2 to 8)

# Define the Normal PDF (N(2,1)) over the sampled range
mu, sigma = 2, 1
normalpdf = norm.pdf(x, mu, sigma)

# Define the Poisson PMF (lambda=2)
def poisson_pmf(k, lam=2):
    return (np.exp(-lam) * (lam ** k)) / factorial(k)

# Generate Poisson PMF samples (Poisson values only for non-negative integers)
poisson_values = np.arange(0, 9)  # Poisson is defined only on non-negative integers
poissonpdf = np.array([poisson_pmf(i) for i in poisson_values])

# Create a new array for the Poisson PMF, zero everywhere except integer points
poisson_pmf_upsampled = np.zeros(len(x))  # Create an array for upsampled Poisson PMF

# Map Poisson values to the correct index in the x array, keeping them at integers
for i, p_val in enumerate(poisson_values):
    index = np.searchsorted(x, p_val)
    if index < len(poisson_pmf_upsampled):  # Ensure index is within bounds
        poisson_pmf_upsampled[index] = poissonpdf[i]

# Perform the convolution
convolved_pdf = np.convolve(normalpdf, poisson_pmf_upsampled, mode='same')

# Properly normalize the convolution result by dividing by the sum of the step size
convolved_pdf /= np.sum(convolved_pdf) * step_size  # Scale to make it a valid PDF

# Shift the convolved PDF by 2 to account for the starting point at -2
x_shifted = x + 2

# Trim the convolved PDF and x-axis values to the range [-2, 8]
mask = (x_shifted >= -2) & (x_shifted <= 8)
x_trimmed = x_shifted[mask]
convolved_pdf_trimmed = convolved_pdf[mask]

# Find the probability that the sum is greater than 3 by integrating (summing) the convolved PDF
sum_greater_than_3 = np.sum(convolved_pdf_trimmed[x_trimmed > 3]) * step_size  # Adjust for step size

# Output the probability
print(f"Probability that the sum is greater than 3: {sum_greater_than_3}")

# Plot the original PDFs and the trimmed convolved result
plt.plot(x, normalpdf, label='Normal PDF (N(2,1))')
plt.plot(x, poisson_pmf_upsampled, label='Poisson PMF (P(2))')
plt.plot(x_trimmed, convolved_pdf_trimmed, label='Convolved PDF (Sum)')
plt.axvline(x=3, color='r', linestyle='--', label='Threshold = 3')
plt.legend()
plt.title('Convolution of Normal and Poisson Distributions')
plt.show()
