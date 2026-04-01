// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DeleteItemFromArray at cJSON.c:2289:20 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1926:23 in cJSON.h
// cJSON_Duplicate at cJSON.c:2769:23 in cJSON.h
// cJSON_ReplaceItemViaPointer at cJSON.c:2353:26 in cJSON.h
// cJSON_Duplicate at cJSON.c:2769:23 in cJSON.h
// cJSON_ReplaceItemInArray at cJSON.c:2402:26 in cJSON.h
// cJSON_Duplicate at cJSON.c:2769:23 in cJSON.h
// cJSON_InsertItemInArray at cJSON.c:2319:26 in cJSON.h
// cJSON_DetachItemViaPointer at cJSON.c:2243:23 in cJSON.h
// cJSON_GetObjectItem at cJSON.c:1968:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DetachItemFromArray at cJSON.c:2279:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
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

static cJSON* create_dummy_json_object() {
    cJSON *object = cJSON_CreateObject();
    if (!object) return NULL;

    cJSON *item = cJSON_CreateNumber(42);
    if (!item) {
        cJSON_Delete(object);
        return NULL;
    }
    cJSON_AddItemToObject(object, "key", item);
    return object;
}

int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy JSON array and object
    cJSON *array = create_dummy_json_array();
    cJSON *object = create_dummy_json_object();
    if (!array || !object) {
        cJSON_Delete(array);
        cJSON_Delete(object);
        return 0;
    }

    int index = Data[0] % 6; // To cover valid and some invalid indices
    cJSON *new_item = cJSON_CreateNumber(99);
    if (!new_item) {
        cJSON_Delete(array);
        cJSON_Delete(object);
        return 0;
    }

    // Fuzz cJSON_DeleteItemFromArray
    cJSON_DeleteItemFromArray(array, index);

    // Fuzz cJSON_ReplaceItemViaPointer
    cJSON *item_to_replace = cJSON_GetArrayItem(array, 0);
    if (item_to_replace && item_to_replace != new_item) {
        cJSON_ReplaceItemViaPointer(array, item_to_replace, cJSON_Duplicate(new_item, 1));
    }

    // Fuzz cJSON_ReplaceItemInArray
    cJSON_ReplaceItemInArray(array, index, cJSON_Duplicate(new_item, 1));

    // Fuzz cJSON_InsertItemInArray
    cJSON_InsertItemInArray(array, index, cJSON_Duplicate(new_item, 1));

    // Fuzz cJSON_DetachItemViaPointer
    cJSON *detached_item = cJSON_DetachItemViaPointer(object, cJSON_GetObjectItem(object, "key"));
    if (detached_item) {
        cJSON_Delete(detached_item);
    }

    // Fuzz cJSON_DetachItemFromArray
    detached_item = cJSON_DetachItemFromArray(array, index);
    if (detached_item) {
        cJSON_Delete(detached_item);
    }

    // Cleanup
    cJSON_Delete(array);
    cJSON_Delete(object);
    cJSON_Delete(new_item);

    return 0;
}