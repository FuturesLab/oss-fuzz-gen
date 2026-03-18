// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_AddObjectToObject at cJSON.c:2219:22 in cJSON.h
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

static void fuzz_cJSON_AddObjectToObject(cJSON *parent, const uint8_t *Data, size_t Size) {
    // Ensure that Data is null-terminated for string operations
    char *name = (char *)malloc(Size + 1);
    if (name == NULL) {
        return;
    }
    memcpy(name, Data, Size);
    name[Size] = '\0';

    // Attempt to add an object to the parent object
    cJSON *child = cJSON_AddObjectToObject(parent, name);
    if (child == NULL) {
        // Handle the error case where the child could not be added
        free(name);
        return;
    }

    // Clean up
    free(name);
}

int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    // Create a new cJSON object
    cJSON *parent = cJSON_CreateObject();
    if (parent == NULL) {
        // Handle memory allocation failure
        return 0;
    }

    // Fuzz the cJSON_AddObjectToObject function
    fuzz_cJSON_AddObjectToObject(parent, Data, Size);

    // Clean up the cJSON object and all its subentities
    cJSON_Delete(parent);

    return 0;
}