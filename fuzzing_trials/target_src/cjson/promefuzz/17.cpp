// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddTrueToObject at cJSON.c:2147:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
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

static void fuzz_cjson_functions(const uint8_t *Data, size_t Size) {
    // Create a cJSON object
    cJSON *object = cJSON_CreateObject();
    if (object == NULL) {
        return; // Memory allocation failed, return early
    }

    // Use a portion of the Data as the key for cJSON_AddTrueToObject
    char key[256];
    size_t key_size = Size < 255 ? Size : 255;
    memcpy(key, Data, key_size);
    key[key_size] = '\0'; // Null-terminate the key string

    // Add a true value to the object
    cJSON *true_item = cJSON_AddTrueToObject(object, key);
    if (true_item == NULL) {
        cJSON_Delete(object);
        return; // Failed to add true value, clean up and return
    }

    // Clean up the cJSON object
    cJSON_Delete(object);
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    fuzz_cjson_functions(Data, Size);
    return 0;
}