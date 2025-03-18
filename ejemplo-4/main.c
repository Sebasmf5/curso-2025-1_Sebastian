// Programa que muestra las llamadas a funciones hechas en assembly

#include <stdio.h>
#include <stdlib.h>

//rax       rdi , rdi
  int sumar(int , int);
  int restar(int, int);

int main(int numeroParametro, char **argumentos){

   int resultado;
   int numero1=5;
   int numero2=6;

   printf("El numero de parametros en la linea de comandos fue %d\r\n", numeroParametro);
   resultado = sumar(numero1, numero2);
   printf("La suma de %d y %d es %d \r\n", numero1, numero2, resultado);

   printf("----------Restar----------\r\n");
   numero1=10;
   numero2=4;
   resultado = restar(numero1, numero2);
   printf("La resta de %d y %d es %d \r\n", numero1, numero2, resultado);
   return(EXIT_SUCCESS);
}
