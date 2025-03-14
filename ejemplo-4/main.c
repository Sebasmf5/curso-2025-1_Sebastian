// Programa que muestra las llamadas a funciones hechas en assembly

#include <stdio.h>
#include <stdlib.h>

//rax       rdi , rdi
  int sumar(int , int);

int main(int numeroParametro, char **argumentos){

   int resultado;
   int numero1=5;
   int numero2=6;

   resultado = sumar(numero1, numero2);
   printf("La suma de %d y %d es %d", numero1, numero2, resultado);

   return(EXIT_SUCCESS);
}
