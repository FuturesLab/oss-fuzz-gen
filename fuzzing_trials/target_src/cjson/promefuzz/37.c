// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_ParseWithLengthOpts at cJSON.c:1142:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_PrintPreallocated at cJSON.c:1343:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_ParseWithLength at cJSON.c:1227:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_ParseWithOpts at cJSON.c:1126:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cJSON.h"

static void fuzz_cJSON_Parse(const uint8_t *Data, size_t Size) {
    char *json_string = (char *)malloc(Size + 1);
    if (json_string == NULL) {
        return;
    }
    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';

    cJSON *json = cJSON_Parse(json_string);
    if (json != NULL) {
        cJSON_Delete(json);
    }

    free(json_string);
}

static void fuzz_cJSON_ParseWithLengthOpts(const uint8_t *Data, size_t Size) {
    const char *end = NULL;
    cJSON *json = cJSON_ParseWithLengthOpts((const char *)Data, Size, &end, 0);
    if (json != NULL) {
        cJSON_Delete(json);
    }
}

static void fuzz_cJSON_PrintUnformatted(const uint8_t *Data, size_t Size) {
    char *json_string = (char *)malloc(Size + 1);
    if (json_string == NULL) {
        return;
    }
    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';

    cJSON *json = cJSON_Parse(json_string);
    if (json != NULL) {
        char *unformatted = cJSON_PrintUnformatted(json);
        if (unformatted != NULL) {
            free(unformatted);
        }
        cJSON_Delete(json);
    }

    free(json_string);
}

static void fuzz_cJSON_PrintPreallocated(const uint8_t *Data, size_t Size) {
    char *json_string = (char *)malloc(Size + 1);
    if (json_string == NULL) {
        return;
    }
    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';

    cJSON *json = cJSON_Parse(json_string);
    if (json != NULL) {
        size_t buffer_size = Size + 5;
        char *buffer = (char *)malloc(buffer_size);
        if (buffer != NULL) {
            cJSON_PrintPreallocated(json, buffer, buffer_size, 0);
            free(buffer);
        }
        cJSON_Delete(json);
    }

    free(json_string);
}

static void fuzz_cJSON_ParseWithLength(const uint8_t *Data, size_t Size) {
    cJSON *json = cJSON_ParseWithLength((const char *)Data, Size);
    if (json != NULL) {
        cJSON_Delete(json);
    }
}

static void fuzz_cJSON_ParseWithOpts(const uint8_t *Data, size_t Size) {
    char *json_string = (char *)malloc(Size + 1);
    if (json_string == NULL) {
        return;
    }
    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';

    const char *end = NULL;
    cJSON *json = cJSON_ParseWithOpts(json_string, &end, 0);
    if (json != NULL) {
        cJSON_Delete(json);
    }

    free(json_string);
}

int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    fuzz_cJSON_Parse(Data, Size);
    fuzz_cJSON_ParseWithLengthOpts(Data, Size);
    fuzz_cJSON_PrintUnformatted(Data, Size);
    fuzz_cJSON_PrintPreallocated(Data, Size);
    fuzz_cJSON_ParseWithLength(Data, Size);
    fuzz_cJSON_ParseWithOpts(Data, Size);
    return 0;
}