import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import r2_score

# Larger trial data for input
x_larger = np.array([93934359, 63331984, 52968592, 28058967, 16661058, 
                     49497226, 16185954, 85712721, 83200838, 37882012])
y_larger = np.array([43709.158, 26640.556, 22154.383, 10267.687, 5868.313, 
                     20312.639, 5540.904, 34704.427, 34120.088, 13860.549])

# Logarithmic model parameters
a_log, b_log, c_log = 11.68941954168165, 1.0709964873330177e-05, 2.1460731625371802e-05

# Linear model parameters
slope_linear, intercept_linear = 0.0003597287731768542, -58.290690312227525

# Define model functions
def logarithmic_model(x):
    return a_log + b_log * x + c_log * x * np.log(x)

def linear_model(x):
    return slope_linear * x + intercept_linear

# Generate predictions for both models
y_log_pred = logarithmic_model(x_larger)
y_linear_pred = linear_model(x_larger)

# Plotting the data points and both trendlines
plt.figure(figsize=(10, 6))
plt.scatter(x_larger, y_larger, color='purple', label='Data Points', s=50)  # Data points
plt.plot(x_larger, y_log_pred, color='red', linestyle='-', linewidth=2, label='Logarithmic Model')  # Logarithmic model
plt.plot(x_larger, y_linear_pred, color='blue', linestyle='-', linewidth=2, label='Linear Model')  # Linear model

# Adding labels and legend
plt.title("Comparison of Logarithmic and Linear Regression Models")
plt.xlabel("Number of Elements")
plt.ylabel("Time (ms)")
plt.legend()
plt.grid(True)
plt.show()
