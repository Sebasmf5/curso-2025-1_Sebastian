#include <stdio.h>
#include <stdlib.h> 

//rax                 (rdi   , rsi , rdx  ) int 
//rax                 (xmm0  , xmm1, xmm2 ) floats | double
//Mezclando:
//rax                  (xmm0 , rdi,  xmm1)
 float calculadoraCiclos(float, int,  float);

int main(){
   
  float pi = 3.1415926535F;
  int ciclos = 5;
  float radio = 2.41F;
  float resultado;
  
  resultado = calculadoraCiclos(pi, ciclos, radio);
  printf("\r\n"); 
  printf("radio: %f, ciclos: %d, resultado: %f",radio, ciclos, resultado);
  printf("\r\n");
  exit(EXIT_SUCCESS);


}
