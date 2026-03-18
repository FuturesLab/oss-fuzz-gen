// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_DeleteItemFromArray at cJSON.c:2289:20 in cJSON.h
// cJSON_Duplicate at cJSON.c:2769:23 in cJSON.h
// cJSON_Duplicate at cJSON.c:2769:23 in cJSON.h
// cJSON_ReplaceItemViaPointer at cJSON.c:2353:26 in cJSON.h
// cJSON_Duplicate at cJSON.c:2769:23 in cJSON.h
// cJSON_ReplaceItemInArray at cJSON.c:2402:26 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_DetachItemFromArray at cJSON.c:2279:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cJSON.h"

static cJSON* create_dummy_array() {
    cJSON *array = cJSON_CreateArray();
    for (int i = 0; i < 5; ++i) {
        cJSON_AddItemToArray(array, cJSON_CreateNumber(i));
    }
    return array;
}

static cJSON* create_dummy_item() {
    return cJSON_CreateString("dummy");
}

int LLVMFuzzerTestOneInput_54(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cJSON *array = create_dummy_array();
    cJSON *item = create_dummy_item();
    cJSON *duplicate = NULL;
    cJSON *detached = NULL;

    // Fuzz index from data
    int index = Data[0] % 5; // Ensure index is within bounds of dummy array

    // Test cJSON_DeleteItemFromArray
    cJSON_DeleteItemFromArray(array, index);

    // Test cJSON_Duplicate
    duplicate = cJSON_Duplicate(item, Data[0] % 2);

    // Test cJSON_ReplaceItemViaPointer
    if (array->child) {
        cJSON_ReplaceItemViaPointer(array, array->child, cJSON_Duplicate(duplicate, cJSON_True)); // Use a duplicate to avoid use-after-free
    }

    // Test cJSON_ReplaceItemInArray
    cJSON_ReplaceItemInArray(array, index, cJSON_Duplicate(item, cJSON_True)); // Use a duplicate to avoid use-after-free

    // Test cJSON_AddItemToArray
    cJSON_AddItemToArray(array, create_dummy_item()); // Add a new item to avoid double free

    // Test cJSON_DetachItemFromArray
    detached = cJSON_DetachItemFromArray(array, index);
    if (detached) {
        cJSON_Delete(detached);
    }

    // Clean up
    cJSON_Delete(array);
    cJSON_Delete(duplicate);
    cJSON_Delete(item);

    return 0;
}