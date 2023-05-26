import scipy.linalg as linalg
import numpy as np
import sympy

#Part B
v = np.array([[1,0,4],[-2,3,-2],[-2,0,6]])
Q, R = np.linalg.qr(v)

print("Value of q: \n",Q)
print("Value of r: \n",R)
