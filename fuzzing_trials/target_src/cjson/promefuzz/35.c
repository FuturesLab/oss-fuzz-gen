// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2183:22 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_DetachItemViaPointer at cJSON.c:2243:23 in cJSON.h
// cJSON_GetObjectItem at cJSON.c:1968:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DetachItemFromArray at cJSON.c:2279:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DeleteItemFromArray at cJSON.c:2289:20 in cJSON.h
// cJSON_GetObjectItem at cJSON.c:1968:23 in cJSON.h
// cJSON_ReplaceItemViaPointer at cJSON.c:2353:26 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_InsertItemInArray at cJSON.c:2319:26 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_ReplaceItemInArray at cJSON.c:2402:26 in cJSON.h
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
    for (int i = 0; i < 5; i++) {
        cJSON_AddItemToArray(array, cJSON_CreateNumber(i));
    }
    return array;
}

static cJSON* create_dummy_json_object() {
    cJSON *object = cJSON_CreateObject();
    cJSON_AddStringToObject(object, "name", "example");
    cJSON_AddNumberToObject(object, "value", 42);
    return object;
}

int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cJSON *array = create_dummy_json_array();
    cJSON *object = create_dummy_json_object();
    cJSON *item = cJSON_CreateNumber(Data[0]);
    int index = Data[0] % 6; // Ensure index is within a reasonable range

    // Test cJSON_DetachItemViaPointer
    cJSON *detached_item = cJSON_DetachItemViaPointer(object, cJSON_GetObjectItem(object, "name"));
    if (detached_item) {
        cJSON_Delete(detached_item);
    }

    // Test cJSON_DetachItemFromArray
    detached_item = cJSON_DetachItemFromArray(array, index);
    if (detached_item) {
        cJSON_Delete(detached_item);
    }

    // Test cJSON_DeleteItemFromArray
    cJSON_DeleteItemFromArray(array, index);

    // Test cJSON_ReplaceItemViaPointer
    cJSON_ReplaceItemViaPointer(object, cJSON_GetObjectItem(object, "value"), cJSON_CreateNumber(100));

    // Test cJSON_InsertItemInArray
    cJSON_InsertItemInArray(array, index, cJSON_CreateNumber(99));

    // Test cJSON_ReplaceItemInArray
    cJSON_ReplaceItemInArray(array, index, cJSON_CreateNumber(77));

    // Cleanup
    cJSON_Delete(array);
    cJSON_Delete(object);
    cJSON_Delete(item);

    return 0;
}