// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddRawToObject at cJSON.c:2207:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "cJSON.h"

static char* create_string_from_data(const uint8_t *Data, size_t Size) {
    char *str = (char *)malloc(Size + 1);
    if (str == NULL) {
        return NULL;
    }
    memcpy(str, Data, Size);
    str[Size] = '\0';
    return str;
}

int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    }

    // Create a new JSON object
    cJSON *object = cJSON_CreateObject();
    if (object == NULL) {
        return 0;
    }

    // Split the input data into two parts
    size_t key_size = Data[0] % Size;
    size_t raw_size = Size - key_size - 1;

    if (key_size == 0 || raw_size == 0) {
        cJSON_Delete(object);
        return 0;
    }

    // Create key and raw JSON string from input data
    char *key = create_string_from_data(Data + 1, key_size);
    char *raw = create_string_from_data(Data + 1 + key_size, raw_size);

    if (key == NULL || raw == NULL) {
        free(key);
        free(raw);
        cJSON_Delete(object);
        return 0;
    }

    // Add raw JSON string to the object
    cJSON *item = cJSON_AddRawToObject(object, key, raw);

    // Clean up
    free(key);
    free(raw);
    cJSON_Delete(object);

    return item != NULL;
}