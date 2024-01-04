import matplotlib.pyplot as plt
import numpy as np
import ctypes

plt.style.use('_mpl-gallery')
x = np.linspace(-10, 10, 999999999)
variables = ctypes.WinDLL('D:/graphing_calc/lib/mydll.dll')
m = ctypes.c_int.in_dll(variables, 'slope')
b = ctypes.c_int.in_dll(variables, 'intercept')
z = ctypes.c_int.in_dll(variables, 'z')
y = m*x + b

fig, ax = plt.subplots()
ax.scatter(x, y)
plt.axis([-20, 20, -20, 20])
plt.grid(True)
plt.show()
