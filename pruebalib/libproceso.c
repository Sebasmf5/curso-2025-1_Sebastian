#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
   int id_proceso;
    int tiempo_rafaga;
    int prioridad;
    int tiempo_llegada;
    int finish;
    int tiempo_inicio;
    int tiempo_fin;
    int tiempo_espera;
    int tiempo_sistema;
} Proceso;

static int trabajo_mas_corto_conteo(Proceso *procesos, int cantidad){
    int reloj = 0;
    int terminados = 0;

    while (terminados < cantidad)
    {
        int idx = -1;
        int menor_time = 9999;
        for (int i = 0; i < cantidad; i++)
        { 
            if(procesos[i].tiempo_llegada <= reloj && procesos[i].finish == 0){ //si está disponible y no ha terminado
                if(procesos[i].tiempo_rafaga < menor_time){                     //si el tiempo de ráfaga es menor
                    menor_time = procesos[i].tiempo_rafaga;
                    idx = i;
                }
            }
        }
        if(idx != -1){ // Si hay un proceso 
            //Establecer tiempo_inicio
            procesos[idx].tiempo_inicio = reloj;
            
            //Establecer tiempo en el sistema
            procesos[idx].tiempo_espera = reloj - procesos[idx].tiempo_llegada;

             //Establecer el tiempo en el sistema
            procesos[idx].tiempo_sistema = procesos[idx].tiempo_espera + procesos[idx].tiempo_rafaga;
           
            //Actualizar el reloj
            reloj += procesos[idx].tiempo_rafaga;
           
            //Establecer tiempo_fin
            procesos[idx].tiempo_fin = reloj;
            //Dar por terminado el proceso
            procesos[idx].finish = 1;
            //Aumentar los procesos terminados
            terminados++;
        }else{
            reloj++;
        }
        
    }
    return reloj;
}


static void generar_diagrama_grant(cJSON * array_diagrama, int tiempo_completo, Proceso *proceso, int cant_procesos){
     for (int i = 0; i < cant_procesos; i++) {
        cJSON *fila = cJSON_CreateArray();
        for (int j = 0; j < tiempo_completo; j++){
            int a;
            if(j < proceso[i].tiempo_llegada){ //Si el procesos no ha llegado
                a=0;
            }else{
                if(j < proceso[i].tiempo_inicio && j>= proceso[i].tiempo_llegada){
                    a = 1;
                }else if(j >= proceso[i].tiempo_inicio && j< proceso[i].tiempo_fin){
                    a = 2;
                }else{
                    a = 0;
                }
            }
            cJSON_AddItemToArray(fila, cJSON_CreateNumber(a));
        }
        cJSON_AddItemToArray(array_diagrama, fila);
     }
}//final funcion generar_diagrama_grant

cJSON * algoritmo_SJF(char * cadena){

    cJSON * entrada = cJSON_Parse(cadena);
    //Objetos para enviar el resultado:
    cJSON *objeto_final = cJSON_CreateObject(); //json que contiene datos de la tabla y el grafico
    cJSON *sistema_espera = cJSON_CreateObject(); //json que contiene tiempo_espera y tiempo_sistema
   
    //Obtener la entrada
    cJSON *array_procesos = cJSON_GetObjectItem(entrada, "procesos"); 
   
    if(array_procesos == NULL){
       cJSON_AddStringToObject(sistema_espera, "error", "No se encontraron procesos");
       cJSON_AddItemToObject(objeto_final, "Sin resultados", sistema_espera);
       return objeto_final;
    }

    // Se obtiene el tamaño
    int size = cJSON_GetArraySize(array_procesos);

    // Se crea el arreglo de procesos para la funcion contar
    Proceso * procesos = (Proceso *)calloc(size, sizeof(Proceso));

    //Se recorre el objeto array
    cJSON *proceso_iterador = cJSON_CreateObject();
    int i = 0;

    cJSON_ArrayForEach(proceso_iterador, array_procesos){
        cJSON *id = cJSON_GetObjectItem(proceso_iterador, "id");
        cJSON *llegada = cJSON_GetObjectItem(proceso_iterador, "llegada");
        cJSON *rafaga = cJSON_GetObjectItem(proceso_iterador, "rafaga");
        cJSON *prioridad = cJSON_GetObjectItem(proceso_iterador, "prioridad");
        //valores de entrada
        procesos[i].id_proceso = id->valueint;
        procesos[i].tiempo_rafaga = rafaga->valueint;
        procesos[i].prioridad = prioridad->valueint;
        procesos[i].tiempo_llegada = llegada->valueint;
        
        i++;
    }

    //Se realiza el conteo y asignacion de valores
    int reloj =  trabajo_mas_corto_conteo(procesos, size);

    // genera objeto que contendrá el arraydiagrama
    cJSON *array_diagrama = cJSON_CreateArray();
    generar_diagrama_grant(array_diagrama, reloj, procesos, size);

   //Se encapsulan los resultados
   for(int i=0; i<size; i++){
     cJSON * proceso_n = cJSON_CreateObject();  
     cJSON_AddNumberToObject(proceso_n, "tiempo_sistema", procesos[i].tiempo_sistema);
     cJSON_AddNumberToObject(proceso_n, "tiempo_espera", procesos[i].tiempo_espera);
     char nombre_proceso[15];
     sprintf(nombre_proceso, "%d", i + 1);
     cJSON_AddItemToObject(sistema_espera, nombre_proceso, proceso_n);
   }//fin for 

   cJSON_AddItemToObject(objeto_final, "Procesos", sistema_espera);
   cJSON_AddItemToObject(objeto_final, "Diagrama", array_diagrama);
   free(procesos);
   return objeto_final;
}


char * parseo_to_string(cJSON * entrada){
    char * resultado = cJSON_Print(entrada);
    return resultado;
}//fin funcion parsear_to_string



