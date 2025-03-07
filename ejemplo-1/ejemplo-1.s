.text

.global _start


_start:

	mov $0x3f, %al
	mov $0xF3, %ah


	# Salir del sistema
	mov $60, %rax # 60 es la funcion exit
	xor %rdi, %rdi # rdi = 0  es mas rapido hacer una operacion logica
	syscall
