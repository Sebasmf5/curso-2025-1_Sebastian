.data
mensaje: .asciz "%ld \n"

.text
.globl main
.extern printf		#Para usar la funcion de la libre de c

main:

	sub $8, %rsp		#Alineacion de datos
	xorq %rbx, %rbx 	#Para inicializar rbx = 0

inicio_bucle:
	incq %rbx		#Incrementar rbx
	# Bloque de impresion
        # printf("%ld \n", rbx);
        #           rdi  , rsi
	mov $mensaje, %rdi
	mov %rbx, %rsi
	xorq %rax, %rax		#rax = 0
	call printf

	CMPQ $10, %rbx		#Resta 10 con rbx y el resultado altera la bandera
	JL inicio_bucle

	addq $8, %rsp   # Alineacion de datos original
        # Salir del sistema
	mov $60, %rax   # Funcion de exit
        xor %rdi, %rdi  # exit(0)
        syscall  

