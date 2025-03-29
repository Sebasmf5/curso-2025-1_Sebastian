#include <stdio.h>
#include <stdlib.h>
#include "libmat.h" //Este archivo de cabecera me informa de las funciones de la biblioteca

int main(int numArgs, char ** args){
   char letra; 
   letra = codificar('a'); // Funcion que devuelva la siguiente letra;
   printf("\r\n");
   printf("%c", letra);
   printf("\r\n");
   
    exit(EXIT_SUCCESS);

}
