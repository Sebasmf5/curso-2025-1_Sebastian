#ifndef LIBPROCESO_H
#define LIBPROCESO_H

#include <cjson/cJSON.h>

char * parseo_to_string(cJSON * entrada);
cJSON * algoritmo_SJF(char * cadena);

#endif

