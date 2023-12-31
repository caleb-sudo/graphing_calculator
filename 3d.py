import matplotlib.pyplot as plt
import numpy as np
import ctypes

plt.style.use('_mpl-gallery')

variables = ctypes.WinDLL("D://graphing_calulator/lib/mylib.dll")
x = ctypes.c_int.in_dll(variables, "x")
y = ctypes.c_int.in_dll(variables, "y")
z = ctypes.c_int.in_dll(variables, "z")

fig, ax = plt.subplots(subplot_kw={"projection": "3d"})

plt.show()
