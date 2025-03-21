

#.data
uno: .float 1.0
cero: .float 0.0


.text
.global comparar_float


# float comparar_float(float, float)
# xmm0  comparar_float(xmm0,  xmm1) xmm0 > xmm1?
comparar_float:
    #compare los registros xmm0 y xmm1
    ucomiss %xmm1, %xmm0 # Compare como escalar float xmm0 con xmm1
    ja mayor 		  # xmm0 > xmm1
menor:
    movss cero(%rip), %xmm0     # xmm0 = cero
    jmp fin

mayor:
    movss uno(%rip), %xmm0      # xmm0 = uno
    ret

fin:
    ret
