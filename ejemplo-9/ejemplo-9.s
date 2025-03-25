
.text

.global calculadoraCiclos

calculadoraCiclos:
   # xmm0 funcion (xmm0, rsi, xmm1)
   mulss %xmm1, %xmm0  # ss signifia S (scalar: escalar) y S (single: float)
  
# Queremos realizar n ciclos (rdi = 5)
# do-while
#clicos:

   #Codigo
   #dec %rdi
   #cmp $0, %rdi      # Comparacion entre rsi y cero
   #jne ciclos        # Podemos usar jne o jnx arbitrariamente 


#Implementacion del while
ciclos:

   cmp $0, %rdi      #Comparacion entre rsi y cero
   je fin            #Podemos usar je o jz arbitrariamente

   addss %xmm0, %xmm0  # xmm0 = xmm0 + xmm0
   dec %rdi
   jmp ciclos

fin:
   ret
