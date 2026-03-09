// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_InitHooks at cJSON.c:209:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_GetArraySize at cJSON.c:1884:19 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "cJSON.h"

int LLVMFuzzerTestOneInput_2(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0; // Ensure there's at least some data to work with

    // Create a string from the input data
    char *inputString = (char *)malloc(Size + 1);
    if (!inputString) return 0;
    memcpy(inputString, Data, Size);
    inputString[Size] = '\0';

    // Create a few cJSON strings
    cJSON *string1 = cJSON_CreateString(inputString);
    cJSON *string2 = cJSON_CreateString(inputString);
    cJSON *string3 = cJSON_CreateString(inputString);

    // Create an array
    cJSON *array = cJSON_CreateArray();

    // Initialize hooks
    cJSON_Hooks hooks;
    hooks.malloc_fn = malloc;
    hooks.free_fn = free;
    cJSON_InitHooks(&hooks);

    // Add items to the array
    cJSON_AddItemToArray(array, string1);
    cJSON_AddItemToArray(array, string2);

    // Check array size
    int arraySize = cJSON_GetArraySize(array);

    // Create an object and add the array and another string to it
    cJSON *object = cJSON_CreateObject();
    cJSON_AddItemToObject(object, "array", array);
    cJSON_AddItemToObject(object, "string", string3);

    // Clean up
    cJSON_Delete(object);

    // Free the allocated input string
    free(inputString);

    return 0;
}