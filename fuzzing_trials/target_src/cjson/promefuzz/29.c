// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_DetachItemFromArray at cJSON.c:2279:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_IsArray at cJSON.c:3027:26 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_DeleteItemFromArray at cJSON.c:2289:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_InsertItemInArray at cJSON.c:2319:26 in cJSON.h
// cJSON_GetArraySize at cJSON.c:1884:19 in cJSON.h
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

static cJSON* create_dummy_json_array() {
    cJSON *array = cJSON_CreateArray();
    if (!array) return NULL;

    for (int i = 0; i < 5; ++i) {
        cJSON *item = cJSON_CreateNumber(i);
        if (!item) {
            cJSON_Delete(array);
            return NULL;
        }
        cJSON_AddItemToArray(array, item);
    }
    return array;
}

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cJSON *array = create_dummy_json_array();
    if (!array) return 0;

    int index = Data[0] % 10; // Simple index derived from input data

    // Test cJSON_DetachItemFromArray
    cJSON *detached_item = cJSON_DetachItemFromArray(array, index);
    if (detached_item) {
        cJSON_Delete(detached_item);
    }

    // Test cJSON_IsArray
    cJSON_bool is_array = cJSON_IsArray(array);

    // Test cJSON_AddItemToArray
    cJSON *new_item = cJSON_CreateString("new_item");
    if (new_item) {
        cJSON_AddItemToArray(array, new_item);
    }

    // Test cJSON_DeleteItemFromArray
    cJSON_DeleteItemFromArray(array, index);

    // Test cJSON_InsertItemInArray
    cJSON *insert_item = cJSON_CreateString("insert_item");
    if (insert_item) {
        cJSON_InsertItemInArray(array, index, insert_item);
    }

    // Test cJSON_GetArraySize
    int array_size = cJSON_GetArraySize(array);

    // Cleanup
    cJSON_Delete(array);

    return 0;
}