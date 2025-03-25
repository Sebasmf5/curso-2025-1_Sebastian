section .data

    fact3 dq  0.166666666666666666   # 1/3!
    fact5 dq  0.0083333333333333333  # 1/5!
    fact7 dq  0.00011984126984126984 # 1/7!

section .text
    globl taylor:

    movapd xmm1, xmm0    #xmm1 = x
    mulpd xmm1, xmm0     # xmm1 = x*x 
    
