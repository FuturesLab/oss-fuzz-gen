// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_AddBoolToObject at cJSON.c:2171:22 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
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

static void fuzz_cJSON_AddBoolToObject(cJSON *object, const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return;
    }

    // Extract a name for the boolean value
    size_t name_len = Data[0] % Size; // Ensure name_len is within bounds
    if (name_len + 1 >= Size) {
        return; // Ensure there's enough data for the boolean value
    }

    char name[name_len + 1];
    memcpy(name, Data + 1, name_len);
    name[name_len] = '\0';

    // Extract the boolean value
    cJSON_bool bool_value = Data[name_len + 1] % 2;

    // Add the boolean to the object
    cJSON *item = cJSON_AddBoolToObject(object, name, bool_value);
    if (!item) {
        // Handle error if item creation fails
        return;
    }
}

int LLVMFuzzerTestOneInput_18(const uint8_t *Data, size_t Size) {
    // Step 1: Create a new cJSON object
    cJSON *object = cJSON_CreateObject();
    if (!object) {
        // Handle error if object creation fails
        return 0;
    }

    // Step 2: Add two boolean values to the object
    fuzz_cJSON_AddBoolToObject(object, Data, Size);
    fuzz_cJSON_AddBoolToObject(object, Data, Size);

    // Step 3: Clean up the cJSON object
    cJSON_Delete(object);

    return 0;
}