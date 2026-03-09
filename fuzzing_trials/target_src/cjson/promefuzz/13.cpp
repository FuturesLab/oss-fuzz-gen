// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddFalseToObject at cJSON.c:2159:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include "cJSON.h"

int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    // Ensure the input data is null-terminated for safe string operations
    char *key = NULL;
    if (Size > 0) {
        key = (char *)malloc(Size + 1);
        if (key == NULL) {
            return 0; // Memory allocation failed, exit early
        }
        memcpy(key, Data, Size);
        key[Size] = '\0'; // Null-terminate the string
    }

    // Create a new cJSON object
    cJSON *object = cJSON_CreateObject();
    if (object == NULL) {
        free(key);
        return 0; // Failed to create object, exit early
    }

    // Add a false value to the object with the given key
    cJSON *result = cJSON_AddFalseToObject(object, key);
    if (result == NULL) {
        // Handle error if adding false to object fails
    }

    // Clean up
    cJSON_Delete(object);
    free(key);

    return 0;
}