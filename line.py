import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(-30, 30, 300)
slope = input("slope: ")
y_int = input("y-intercept: ")
y = int(slope) * x + int(y_int)

plt.plot(x, y)
plt.grid(True)
plt.show()
