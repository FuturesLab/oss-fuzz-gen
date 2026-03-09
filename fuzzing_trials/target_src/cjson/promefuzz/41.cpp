// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_IsArray at cJSON.c:3027:26 in cJSON.h
// cJSON_GetArraySize at cJSON.c:1884:19 in cJSON.h
// cJSON_DeleteItemFromArray at cJSON.c:2289:20 in cJSON.h
// cJSON_DetachItemFromArray at cJSON.c:2279:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_InsertItemInArray at cJSON.c:2319:26 in cJSON.h
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
#include <stdbool.h>
#include "cJSON.h"

static cJSON* create_random_cjson_array(const uint8_t *Data, size_t Size) {
    cJSON *array = cJSON_CreateArray();
    if (!array) return NULL;

    for (size_t i = 0; i < Size; ++i) {
        cJSON *item = cJSON_CreateNumber(Data[i]);
        if (!item || !cJSON_AddItemToArray(array, item)) {
            cJSON_Delete(item);
            break;
        }
    }

    return array;
}

int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    cJSON *array = create_random_cjson_array(Data, Size);
    if (!array) return 0;

    // Test cJSON_IsArray
    bool isArray = cJSON_IsArray(array);

    // Test cJSON_GetArraySize
    int arraySize = cJSON_GetArraySize(array);

    // Test cJSON_DeleteItemFromArray
    if (arraySize > 0) {
        int indexToDelete = Data[0] % arraySize;
        cJSON_DeleteItemFromArray(array, indexToDelete);
    }

    // Test cJSON_DetachItemFromArray
    if (arraySize > 1) {
        int indexToDetach = Data[1] % (arraySize - 1);
        cJSON *detachedItem = cJSON_DetachItemFromArray(array, indexToDetach);
        cJSON_Delete(detachedItem);
    }

    // Test cJSON_InsertItemInArray
    if (arraySize > 0 && Size > 3) {
        int indexToInsert = Data[2] % arraySize;
        cJSON *newItem = cJSON_CreateNumber(Data[3]);
        if (newItem) {
            cJSON_InsertItemInArray(array, indexToInsert, newItem);
        }
    }

    // Clean up
    cJSON_Delete(array);
    return 0;
}