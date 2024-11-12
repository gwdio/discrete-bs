import numpy as np
from sklearn.metrics import r2_score

# Larger trial data
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

# Predict y values with both models
y_pred_log = logarithmic_model(x_larger)
y_pred_linear = linear_model(x_larger)

# Calculate R-squared values
r2_log_calculated = r2_score(y_larger, y_pred_log)
r2_linear_calculated = r2_score(y_larger, y_pred_linear)

print("R-squared (Logarithmic Model):", r2_log_calculated)
print("R-squared (Linear Model):", r2_linear_calculated)
