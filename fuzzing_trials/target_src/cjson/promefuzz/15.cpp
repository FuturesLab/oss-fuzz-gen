// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2435:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

int LLVMFuzzerTestOneInput_15(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) * 2 + 1) {
        return 0;
    }

    // Extract two double values from the input data
    double num1;
    double num2;
    memcpy(&num1, Data, sizeof(double));
    memcpy(&num2, Data + sizeof(double), sizeof(double));

    // Ensure the key is null-terminated
    size_t key_length = Size - 2 * sizeof(double);
    char *key = (char *)malloc(key_length + 1);
    if (!key) {
        return 0;
    }
    memcpy(key, Data + 2 * sizeof(double), key_length);
    key[key_length] = '\0';

    // Create two cJSON number items
    cJSON *number1 = cJSON_CreateNumber(num1);
    cJSON *number2 = cJSON_CreateNumber(num2);

    if (!number1 || !number2) {
        cJSON_Delete(number1);
        cJSON_Delete(number2);
        free(key);
        return 0;
    }

    // Create a cJSON object
    cJSON *jsonObject = cJSON_CreateObject();
    if (!jsonObject) {
        cJSON_Delete(number1);
        cJSON_Delete(number2);
        free(key);
        return 0;
    }

    // Add the first number item to the object
    if (!cJSON_AddItemToObject(jsonObject, key, number1)) {
        cJSON_Delete(number1);
        cJSON_Delete(number2);
        cJSON_Delete(jsonObject);
        free(key);
        return 0;
    }

    // Replace the item in the object with the second number item
    cJSON_ReplaceItemInObject(jsonObject, key, number2);

    // Clean up
    cJSON_Delete(jsonObject);
    free(key);

    return 0;
}