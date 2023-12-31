import matplotlib.pyplot as plt
import numpy as np
import ctypes

plt.style.use('_mpl-gallery')

variables = ctypes.WinDLL("D://graphing_calculator/lib/graph.dll")
x = ctypes.c_int.in_dll(variables, "x")
y = ctypes.c_int.in_dll(variables, "y")

plt.plot([x], [y], "ro")
x_means = x.mean()
y_means = y.mean()
plt.plot([x_means], [y_means], "go")

plt.axis([-20,20,-20,20])

x_minus_x_means = x - x_means
y_minus_y_means = y - y_means
x_minus_x_means_squared = x_minus_x_means**2
x_minus_x_means_times_y_minus_y_means = x_minus_x_means * y_minus_y_means

m = sum(x_minus_x_means_times_y_minus_y_means) / sum(x_minus_x_means_squared)
b = y_means - m * x_means

plt.show()
