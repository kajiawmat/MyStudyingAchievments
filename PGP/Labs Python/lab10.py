import numpy
from numba import jit
from numba import cuda
from time import perf_counter_ns as timer
from numba import cuda, float32

@cuda.jit(argtypes=[float32[:,:],float32[:,:],float32[:,:]])
def matmul(A,B,C):
    m,n=cuda.grid(2)
    if m<C.shape[0] and n<C.shape[1]:
         acc=0.
         for k in range(A.shape[1]):
             acc +=A[m,k]*B[k,n]
         C[m,n]=acc


N=64
M=32
K=32

numpy.set_printoptions(formatter={'float': '{:0.3g}'.format})
for i in range(6):
    A=numpy.arange(M*K)
    A=A.reshape(M,K)
    B=numpy.ones((K,N))
    C=numpy.zeros((M,N))
    A=numpy.float32(A)
    B=numpy.float32(B)
    C=numpy.float32(C)

    start=timer()
    C=numpy.matmul(A,B)
    stop=timer()
    dt=(stop-start)/1000000.0
    print("np.matmul time %f ms" % dt)
    print(C)

    C=numpy.float32(C)
    dA=cuda.to_device(A)
    dB=cuda.to_device(B)
    dC=cuda.to_device(C)

    start=timer()
    matmul[(int(N/32),int(M/32)),(32,32)](dA,dB,dC)
    cuda.synchronize()
    stop=timer()
    dt=(stop-start)/1000000.0

    dC.to_host()
    print("cuda matmul time %f ms" % dt)
    print(C)
    K*=2
    

