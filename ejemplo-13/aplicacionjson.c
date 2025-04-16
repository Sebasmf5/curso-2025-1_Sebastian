#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

cJSON * procesarJSON(cJSON * entrada) {
        cJSON * respuesta = cJSON_CreateObject();       // crea un objeto cjson vacio
        cJSON * mensaje = cJSON_GetObjectItem(entrada, "mensaje");      // traigo el elemento mensaje
        if (mensaje != NULL) {
                // le agrego el texto de mensaje a el elemento mensaje original al objeto respuesta
                cJSON_AddItemToObject(respuesta, "mensaje_original", cJSON_Duplicate(mensaje, 1));
        }
        return respuesta;
}

int main(int numArgs, char ** args) {
        // Creamos un JSON string de entrada
        char * json_string = "{\"mensaje\": \"Este es el mensaje original\"}";
        cJSON* objJsonEntrada = cJSON_Parse(json_string);
        if (objJsonEntrada == NULL) {
                printf("Error en la decodificacion del json\r\n");
                return -1;
        }

        // Modificamos el JSON de entrada
        cJSON * respuesta = procesarJSON(objJsonEntrada);
        // Convertimos el objeto JSON en una cadena
        char * cadena = cJSON_Print(respuesta);
        printf("El JSON es : %s\r\n", cadena);

        // Liberando memoria del objeto que ya no es necesario
        cJSON_Delete(respuesta);
        cJSON_Delete(objJsonEntrada);

        free(cadena);
        exit(EXIT_SUCCESS);
}
