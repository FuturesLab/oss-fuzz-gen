// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DeleteItemFromArray at cJSON.c:2289:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_ReplaceItemViaPointer at cJSON.c:2353:26 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_ReplaceItemInArray at cJSON.c:2402:26 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_InsertItemInArray at cJSON.c:2319:26 in cJSON.h
// cJSON_DetachItemViaPointer at cJSON.c:2243:23 in cJSON.h
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
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

static cJSON* create_dummy_json_array() {
    cJSON *array = cJSON_CreateArray();
    if (array) {
        for (int i = 0; i < 5; ++i) {
            cJSON_AddItemToArray(array, cJSON_CreateNumber(i));
        }
    }
    return array;
}

static cJSON* create_dummy_json_object() {
    cJSON *object = cJSON_CreateObject();
    if (object) {
        cJSON_AddItemToObject(object, "key", cJSON_CreateString("value"));
    }
    return object;
}

int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cJSON *array = create_dummy_json_array();
    cJSON *object = create_dummy_json_object();
    if (!array || !object) {
        cJSON_Delete(array);
        cJSON_Delete(object);
        return 0;
    }

    int index = Data[0] % 5; // Ensure index is within bounds for initial array

    // Test cJSON_DeleteItemFromArray
    cJSON_DeleteItemFromArray(array, index);

    // Test cJSON_ReplaceItemViaPointer
    cJSON *newItem = cJSON_CreateString("new");
    if (newItem && array->child) {
        cJSON_ReplaceItemViaPointer(array, array->child, newItem);
    }

    // Test cJSON_ReplaceItemInArray
    newItem = cJSON_CreateString("replaced");
    if (newItem) {
        cJSON_ReplaceItemInArray(array, index, newItem);
    }

    // Test cJSON_InsertItemInArray
    newItem = cJSON_CreateString("inserted");
    if (newItem) {
        cJSON_InsertItemInArray(array, index, newItem);
    }

    // Test cJSON_DetachItemViaPointer
    if (array->child) {
        cJSON *detachedItem = cJSON_DetachItemViaPointer(array, array->child);
        cJSON_Delete(detachedItem);
    }

    // Test cJSON_DetachItemFromArray
    cJSON *detachedItem = cJSON_DetachItemFromArray(array, index);
    cJSON_Delete(detachedItem);

    cJSON_Delete(array);
    cJSON_Delete(object);

    return 0;
}