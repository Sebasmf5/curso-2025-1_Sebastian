#include <stdio.h>
#include <math.h> //para convertir a radianes y facilitar los calculos
#include <stdlib.h>

//xmm0              rid      rsi   rdx
void calcularSeno(double[2], int, double[2]);

int main(){
    double angulo1 = 30;
    double angulo2 = 90;
    int no_nulos = 5;
    
    double angulos[2] = {
           angulo1* (M_PI/180.0),
           angulo2* (M_PI/180.0)
    };

    double resultado[2];
    calcularSeno(angulos, no_nulos, resultado);
    
    printf("El seno de 45 grados es = %lf\r\n",resultado[0]);
    printf("El seno de 30 grados es = %lf\r\n", resultado[1]);
    exit(EXIT_SUCCESS);
}
