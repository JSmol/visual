import numpy as np
# Only works on vectors with size that is an integer power of 2.
def fft(A, omega):
    if len(A) == 1: return A
    n = len(A)

    # for x in (np.real(np.array(A))):
    #     print(f"{x:.2f}", end=' ')
    # print()
    
    # Each has degree n/2.
    r1 = [A[i] + A[i+(n//2)] for i in range(n//2)]
    r2 = [omega**i * (A[i] - A[i+(n//2)]) for i in range(n//2)]
    
    # Compute the fft of r1, r2, rearrange the entries in proper order.
    res = [fft(r1, omega**2), fft(r2, omega**2)]
    rv = np.array([res[i % 2][i // 2] for i in range(n)])
    return rv

    

a = [ 1, 2, 3, 4, 5, 6, 7, 8, 2, 2, 2, 2, 5, 5, 4, 4 ]
print(np.real(fft(a, np.exp(2 * np.pi * 1j / 16))))
