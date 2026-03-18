// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateArrayReference at cJSON.c:2556:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "cJSON.h"

int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0;
    }

    // Create a JSON array
    cJSON *jsonArray = cJSON_CreateArray();
    if (!jsonArray) {
        return 0;
    }

    // Read a double value from the input data
    double num;
    memcpy(&num, Data, sizeof(double));

    // Create a JSON number
    cJSON *jsonNumber = cJSON_CreateNumber(num);
    if (!jsonNumber) {
        cJSON_Delete(jsonArray);
        return 0;
    }

    // Add the number to the array
    cJSON_bool success = cJSON_AddItemToArray(jsonArray, jsonNumber);
    if (!success) {
        cJSON_Delete(jsonNumber);
        cJSON_Delete(jsonArray);
        return 0;
    }

    // Create a reference to the array
    cJSON *arrayRef = cJSON_CreateArrayReference(jsonArray);
    if (!arrayRef) {
        cJSON_Delete(jsonArray);
        return 0;
    }

    // Clean up
    cJSON_Delete(arrayRef);
    cJSON_Delete(jsonArray);

    return 0;
}