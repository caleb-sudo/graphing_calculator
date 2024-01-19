import matplotlib.pyplot as plt
import numpy as np

x = np.linspace(-20, 20, 300)
print("")
c = input("")
if (c == 1):
    m = input("slope: ")
    b = input("y-intercept")
    y = int(m) * x + int(b)
    plt.plot(x, y)
if (c == 2):
    a = input("")
    B = input("")
    c = input("")
    0 = int(a) * x + int(B) * y + int(c)
    plt.plot(x, y)
if (c == 3):
    for(i = 0; i < 1; i++):
        xs = input(""*i)
        ys = input(""*i)
        plt.plot(xs, ys)
if (c == 4):


plt.grif(True)
plt.show()
