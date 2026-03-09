// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddNullToObject at cJSON.c:2135:22 in cJSON.h
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

int LLVMFuzzerTestOneInput_19(const uint8_t *Data, size_t Size) {
    // Ensure that the data is null-terminated and non-empty for a valid string key
    if (Size == 0 || Data[Size - 1] != '\0') {
        return 0;
    }

    // Create a new cJSON object
    cJSON *json_object = cJSON_CreateObject();
    if (json_object == NULL) {
        return 0; // Memory allocation failed
    }

    // Use the input data as the key for the null object
    const char *key = (const char *)Data;

    // Add a null item to the JSON object
    cJSON *null_item = cJSON_AddNullToObject(json_object, key);
    if (null_item == NULL) {
        // Failed to add null item, delete the JSON object and return
        cJSON_Delete(json_object);
        return 0;
    }

    // Cleanup: delete the JSON object and its subentities
    cJSON_Delete(json_object);

    return 0;
}