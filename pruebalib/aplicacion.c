#include <stdlib.h>
#include <stdio.h>
#include <libproceso.h>

int main(int numArgs, char ** args){

 char * procesos=
  "{"
        "  \"procesos\": ["
        "    { \"id\": 1, \"llegada\": 0, \"rafaga\": 10, \"prioridad\": 3},"
        "    { \"id\": 2, \"llegada\": 2, \"rafaga\": 8, \"prioridad\": 2 },"
        "    { \"id\": 3, \"llegada\": 4, \"rafaga\": 6, \"prioridad\": 1 },"
        "    { \"id\": 4, \"llegada\": 6, \"rafaga\": 4, \"prioridad\": 1 },"
        "    { \"id\": 5, \"llegada\": 8, \"rafaga\": 2, \"prioridad\": 1 }"
        "  ]"
        "}";
   char * respuesta;
   respuesta = parseo_to_string(algoritmo_SJF(procesos));
   printf("El json es: %s \r\n", respuesta);
   free(respuesta);


   exit(EXIT_SUCCESS);
}
