.data

signo: .double -1.0, -1.0		 # Constante -1 para alternar signos
uno: .double 1.0, 1.0  		 # 2n+1
dos: .double 2.0, 2.0		 # 2n -> Vector constante 2.0 para incrementar fact 
n: .double 1.0, 1.0 		 # Vector  que almacena el enesimo factorial
fact_actual: .double 1.0, 1.0    # Almacena el valor del factorial actual
 
.text
.globl calcularSeno

calcularSeno:
   #void funcion (double[2] angulos, iteraciones, double[2]resultado)
   #void funcion (rdi,               rsi           rdx) 
   #Argumentos
   #xmm0 = x (angulo en radianes)
   #rsi = numero de iteraciones

   movapd (%rdi), %xmm0			#carga dos valores de 64bits desde la direccion de rdi
   movapd %xmm0, %xmm1			#xmm1 = x (primer termino de la serie de taylor)
   movapd %xmm0, %xmm2			#En xmm2 se llevará la suma acumulada Tn-1 + Tn
   movapd %xmm0, %xmm3			#Este registro tendrá en cuenta las potencias x^n * x^2
   movapd signo(%rip), %xmm4  	        #  xmm4 = [signo, signo]
   movapd fact_actual(%rip), %xmm5      #Acumulador de factorial
   movapd n(%rip), %xmm6      		#Carga el valor de n!

while_taylor:

   cmp $0, %rsi				#comparacion entre rsi y cero
   je fin

   #Calcular el termino siguiente
   # T = T * (x^2) / ((2n+1)(2n))
   mulpd %xmm0, %xmm3			# xmm3 = x^n*x
   mulpd %xmm0, %xmm3			# xmm3 = x^n * x^2 (listo el numerador)

   #Calcular el factorial (2n+1)(2n)(2n-1)!
   #2n
   movapd %xmm6, %xmm7
   mulpd dos(%rip), %xmm7   	        #2n
   movapd %xmm7, %xmm8	     	        #carga 2n
   addpd uno(%rip), %xmm8               #2n+1
   mulpd %xmm7, %xmm8                   #(2n+1)*(2n)
   mulpd %xmm8, %xmm5	                #Nuevo factorial

  #Division
   movapd %xmm3, %xmm9                  #xmm9 = xmm3
   movapd %xmm5, %xmm10                 #xmm10 = xmm5
   divpd %xmm10,  %xmm9		        #xmm9 = [xmm9_alta/xmm10_alta, xmm9_baja/xmm10_baja]
   mulpd %xmm4,  %xmm9	                #Signo

   addpd %xmm9, %xmm2	                #sumar Tn-1 + Tn

  #Actualizar valores
   addpd uno(%rip), %xmm6		#n++
   mulpd signo(%rip), %xmm4            #Modifica el signo
  
   dec %rsi
   jmp while_taylor

fin:
  movapd %xmm2, (%rdx)
  ret


 
