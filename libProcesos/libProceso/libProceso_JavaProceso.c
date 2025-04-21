#include <stdio.h>
#include <jni.h>
#include <cjson/cJSON.h>
#include "libProceso_JavaProceso.h"
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

static int trabajo_mas_corto_conteo(Proceso *procesos, int cantidad) {
    int reloj = 0;
    int terminados = 0;

    while (terminados < cantidad) {
        int idx = -1;
        int menor_time = 9999;
        for (int i = 0; i < cantidad; i++) {
            if (procesos[i].tiempo_llegada <= reloj && procesos[i].finish == 0) { //si está disponible y no ha terminado
                if (procesos[i].tiempo_rafaga < menor_time) { //si el tiempo de ráfaga es menor
                    menor_time = procesos[i].tiempo_rafaga;
                    idx = i;
                }
            }
        }
        if (idx != -1) { // Si hay un proceso
            procesos[idx].tiempo_inicio = reloj;
            procesos[idx].tiempo_espera = reloj - procesos[idx].tiempo_llegada;
            procesos[idx].tiempo_sistema = procesos[idx].tiempo_espera + procesos[idx].tiempo_rafaga;
            reloj += procesos[idx].tiempo_rafaga;
            procesos[idx].tiempo_fin = reloj;
            procesos[idx].finish = 1;
            terminados++;
        } else {
            reloj++;
        }
    }
    return reloj;
}


static void generar_diagrama_grant(cJSON *array_diagrama, int tiempo_completo, Proceso *proceso, int cant_procesos) {
    for (int i = 0; i < cant_procesos; i++) {
        cJSON *fila = cJSON_CreateArray();
        for (int j = 0; j < tiempo_completo; j++) {
            int a;
            if (j < proceso[i].tiempo_llegada) {
                a = 0; // Si el proceso no ha llegado
            } else {
                if (j < proceso[i].tiempo_inicio && j >= proceso[i].tiempo_llegada) {
                    a = 1;
                } else if (j >= proceso[i].tiempo_inicio && j < proceso[i].tiempo_fin) {
                    a = 2;
                } else {
                    a = 0;
                }
            }
            cJSON_AddItemToArray(fila, cJSON_CreateNumber(a));
        }
        cJSON_AddItemToArray(array_diagrama, fila);
    }
}

/*
 * Class:     libProceso_JavaProceso
 * Method:    algoritmo_SJF
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_libProceso_JavaProceso_algoritmo_1SJF
  (JNIEnv * env, jobject obj, jstring json){

    const char *json_input = (*env)->GetStringUTFChars(env, json, 0);
    cJSON *entrada = cJSON_Parse(json_input); // Parseo de la cadena JSON
    cJSON *objeto_final = cJSON_CreateObject();
    cJSON *sistema_espera = cJSON_CreateObject();

    cJSON *array_procesos = cJSON_GetObjectItem(entrada, "procesos");
    if (array_procesos == NULL) {
        cJSON_AddStringToObject(sistema_espera, "error", "No se encontraron procesos");
        cJSON_AddItemToObject(objeto_final, "Sin resultados", sistema_espera);
        char *resultado = cJSON_Print(objeto_final); // Convertir a string JSON
        jstring salida = (*env)->NewStringUTF(env, resultado); //parseo a jstring
        // limpieza
        free(resultado);
        cJSON_Delete(entrada);
        cJSON_Delete(objeto_final);
        (*env)->ReleaseStringUTFChars(env, json, json_input);
        return salida;
    }

    int size = cJSON_GetArraySize(array_procesos);
    Proceso *procesos = (Proceso *)calloc(size, sizeof(Proceso));

    cJSON *proceso_iterador = NULL;
    int i = 0;

    cJSON_ArrayForEach(proceso_iterador, array_procesos) {
        cJSON *id = cJSON_GetObjectItem(proceso_iterador, "id");
        cJSON *llegada = cJSON_GetObjectItem(proceso_iterador, "llegada");
        cJSON *rafaga = cJSON_GetObjectItem(proceso_iterador, "rafaga");
        cJSON *prioridad = cJSON_GetObjectItem(proceso_iterador, "prioridad");
        procesos[i].id_proceso = id->valueint;
        procesos[i].tiempo_rafaga = rafaga->valueint;
        procesos[i].prioridad = prioridad->valueint;
        procesos[i].tiempo_llegada = llegada->valueint;
        i++;
    }

    int reloj = trabajo_mas_corto_conteo(procesos, size);
    cJSON *array_diagrama = cJSON_CreateArray();
    generar_diagrama_grant(array_diagrama, reloj, procesos, size);

    for (int i = 0; i < size; i++) {
        cJSON *proceso_n = cJSON_CreateObject();
        cJSON_AddNumberToObject(proceso_n, "tiempo_sistema", procesos[i].tiempo_sistema);
        cJSON_AddNumberToObject(proceso_n, "tiempo_espera", procesos[i].tiempo_espera);
        char nombre_proceso[15];
        sprintf(nombre_proceso, "%d", procesos[i].id_proceso);
        cJSON_AddItemToObject(sistema_espera, nombre_proceso, proceso_n);
    }

    cJSON_AddItemToObject(objeto_final, "Procesos", sistema_espera);
    cJSON_AddItemToObject(objeto_final, "Diagrama", array_diagrama);

    char *resultado = cJSON_Print(objeto_final); // Convertir la salida a cadena JSON
    jstring salida = (*env)->NewStringUTF(env, resultado);
    cJSON_Delete(entrada);
    cJSON_Delete(objeto_final);
    free(procesos);
    free(resultado);
    (*env)->ReleaseStringUTFChars(env, json, json_input);
    return salida;
}
