import scipy.linalg as linalg
import numpy as np
import sympy
import matplotlib.pyplot as plt

data = np.loadtxt("dataset1.txt")
a,b = np.hsplit(data,2)
p,res,rnk,s = np.linalg.lstsq(a,b,rcond=None)
plt.plot(a,b,'o',label="Original data",markersize=10)
plt.plot(a,p*a +res,'r',label='Fitted Line')
plt.legend()
plt.show()
#Gave up, dont know how to implement fitted line
