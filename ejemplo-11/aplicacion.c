#include <stdio.h>
#include <stdlib.h>
#include <libcubo.h>

int main(int numArgs, char ** args){

   int numero = 8;
   int resultado;
   
   resultado = multiplicarPorOcho(numero);

   printf("\r\n");
   printf("El numero %d multiplicado por 8 es %d ", numero, resultado);
   printf("\r\n");

   exit(EXIT_SUCCESS);
}
