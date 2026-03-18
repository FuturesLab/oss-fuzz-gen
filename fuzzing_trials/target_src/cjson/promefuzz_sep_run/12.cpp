// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Duplicate at cJSON.c:2769:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DetachItemFromArray at cJSON.c:2279:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "cJSON.h"

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    // Create three JSON arrays
    cJSON *array1 = cJSON_CreateArray();
    cJSON *array2 = cJSON_CreateArray();
    cJSON *array3 = cJSON_CreateArray();

    if (!array1 || !array2 || !array3) {
        cJSON_Delete(array1);
        cJSON_Delete(array2);
        cJSON_Delete(array3);
        return 0;
    }

    // Add the second array to the first array
    if (!cJSON_AddItemToArray(array1, array2)) {
        cJSON_Delete(array1);
        cJSON_Delete(array2); // array2 is already added to array1, so it will be deleted with array1
        cJSON_Delete(array3);
        return 0;
    }

    // Add the third array to the first array
    if (!cJSON_AddItemToArray(array1, array3)) {
        cJSON_Delete(array1);
        cJSON_Delete(array3); // array3 is already added to array1, so it will be deleted with array1
        return 0;
    }

    // Duplicate the first array
    cJSON *duplicate = cJSON_Duplicate(array1, 1);
    if (!duplicate) {
        cJSON_Delete(array1);
        return 0;
    }

    // Detach the first item from the duplicated array
    cJSON *detachedItem = cJSON_DetachItemFromArray(duplicate, 0);
    if (detachedItem) {
        cJSON_Delete(detachedItem);
    }

    // Clean up
    cJSON_Delete(array1);
    cJSON_Delete(duplicate);

    return 0;
}