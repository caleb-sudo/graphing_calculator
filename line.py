import matplotlib.pyplot as plt
import ctypes
import numpy as np

plt.style.use('_mpl-gallery')

variables = ctypes.WinDLL("D://graphing_calculator/lib/graph.dll")
x = ctypes.c_int.int_dll(variables, "x")
y = ctypes.c_int.int_dll(variables, "y")
xlimx = ctypes.c_int.in_dll(variables, "xlimx")
xlimy = ctypes.c_int.in_dll(variables, "xlimy")
ylimx = ctypes.c_int.in_dll(variables, "ylimx")
ylimy = ctypes.c_int_dll(variables, "ylimy")

plt.plot([x], [y], "ro")
x_means = x.mean()
y_means = y.mean()
plt.plot([x_means], [y_means], "go")

x_minus_x_means = x - x_means
y_minus_y_means = y - y_means
x_minus_x_means_squared = x_minus_x_means**2
x_minus_x_means_times_y_minus_y_means = x_minus_x_means * y_minus_y_means

m = sum(x_minus_x_means_times_y_minus_y_means) / sum(x_minus_x_means_squared)
b = y_means - m * x_means

plt.axis([-20, 20, -20, 20])
plt.show()
