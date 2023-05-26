import scipy.linalg as linalg
import numpy as np
import sympy

#Part A
def cos_sim(u,v):
    unorm=np.sqrt(sum(u**2))
    vnorm=np.sqrt(sum(v**2))
    answer = np.dot(u,v)/(unorm*vnorm)
    print("The answer is: ",answer)

#Part B
u1 = np.array([3,-1,4])
v1 = np.array([-2,3,1])
cos_sim(u1,v1)
u2 = np.array([5,6,-5])
v2 = np.array([6,2,-5])
cos_sim(u2,v2)
u3 = np.array([-3,1,7])
v3 = np.array([7,-4,7])
cos_sim(u3,v3)
