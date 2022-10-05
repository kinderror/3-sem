import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('dataProb.txt')
x = data[:,0]
y = (data[:,1] - x * 1.0 / 1000) / (x * 1.0 / 1000)
#y_th = x * 1.0 / 1000
fig, ax = plt.subplots()
ax.plot(x, y)
#ax.plot(x, y_th)
plt.show()

