import scipy.linalg as linalg
import numpy as np
import sympy

#Part B
v = np.array([[1,-2],[-4,1]])
value, vector = np.linalg.eig(v)

print("Eigenvalue\n",value)
print("Eigenvector\n",vector)
