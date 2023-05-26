import scipy.linalg as linalg
import numpy as np
import sympy

a = np.array([[-7,0,-3],[7,-1,0],[5,-1,0]])
#Part A
print("A) Compute the reduced echelon form of A and convert the result back to a numpy array. You will need sympy to compute the reduced echelon form.\n")
reducedA = sympy.Matrix(a)
numpyA = reducedA.rref()
numpyA = np.array(numpyA[0].tolist())
print("Matrix A is reduced below\n",numpyA)

#PartB
print("B) Find the column space of A.\n")
print(a)

#PartC
print("\nC) Solve the matrix equation Ax=b.")
b = np.array([[-10],[5],[3]])
answer = linalg.solve(a,b)
print(answer)

#PartD
print("\nD) Compute Nul A.")
nullAnswer =  linalg.null_space(a)
print(nullAnswer)
print("\nProgram Done")
