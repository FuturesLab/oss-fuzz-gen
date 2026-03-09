// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateNull at cJSON.c:2446:23 in cJSON.h
// cJSON_CreateNull at cJSON.c:2446:23 in cJSON.h
// cJSON_CreateNull at cJSON.c:2446:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_free at cJSON.c:3187:20 in cJSON.h
// cJSON_free at cJSON.c:3187:20 in cJSON.h
// cJSON_free at cJSON.c:3187:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_free at cJSON.c:3187:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_free at cJSON.c:3187:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_free at cJSON.c:3187:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "cJSON.h"

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    // Create three cJSON null items
    cJSON *nullItem1 = cJSON_CreateNull();
    cJSON *nullItem2 = cJSON_CreateNull();
    cJSON *nullItem3 = cJSON_CreateNull();

    // Create a cJSON array
    cJSON *array = cJSON_CreateArray();
    if (array == NULL) {
        cJSON_free(nullItem1);
        cJSON_free(nullItem2);
        cJSON_free(nullItem3);
        return 0;
    }

    // Add the null items to the array
    if (!cJSON_AddItemToArray(array, nullItem1)) {
        cJSON_free(nullItem1);
    }
    if (!cJSON_AddItemToArray(array, nullItem2)) {
        cJSON_free(nullItem2);
    }
    if (!cJSON_AddItemToArray(array, nullItem3)) {
        cJSON_free(nullItem3);
    }

    // Free the array, which should also free its contents
    cJSON_Delete(array);

    return 0;
}