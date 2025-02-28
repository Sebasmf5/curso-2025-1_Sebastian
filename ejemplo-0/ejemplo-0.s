.data
mensaje: .string  "Hola mundo\n"

.text
.global _start # Hacemos a el procedimiento _start publico

_start:
        #Aqui empieza el codigo de la aplicacion
        mov $1, %rax             # rax=1
        mov $1, %rdi             # rdi=1
        mov $mensaje, %rsi       # rsi = direccion donde inicia el mensaje
        mov $11, %rdx            # rdx = 11
        syscall                  # llamamos al sistema

        mov $60, %rax            # rax = 60
        xor %rdi, %rdi           # rdi=rdi (xo) rdi
        syscall                  # llamamos al sistema
