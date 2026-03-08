// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2183:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DetachItemFromObjectCaseSensitive at cJSON.c:2301:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DetachItemFromObject at cJSON.c:2294:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2308:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2435:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_HasObjectItem at cJSON.c:1978:26 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2313:20 in cJSON.h
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

static cJSON *create_dummy_json_object() {
    cJSON *object = cJSON_CreateObject();
    cJSON_AddStringToObject(object, "key1", "value1");
    cJSON_AddStringToObject(object, "Key2", "value2");
    cJSON_AddNumberToObject(object, "key3", 123);
    return object;
}

int LLVMFuzzerTestOneInput_37(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy JSON object
    cJSON *json_object = create_dummy_json_object();
    if (!json_object) return 0;

    // Prepare a key string from input data
    char *key = (char *)malloc(Size + 1);
    if (!key) {
        cJSON_Delete(json_object);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';

    // Test cJSON_DetachItemFromObjectCaseSensitive
    cJSON *detached_item1 = cJSON_DetachItemFromObjectCaseSensitive(json_object, key);
    if (detached_item1) {
        cJSON_Delete(detached_item1);
    }

    // Test cJSON_DetachItemFromObject
    cJSON *detached_item2 = cJSON_DetachItemFromObject(json_object, key);
    if (detached_item2) {
        cJSON_Delete(detached_item2);
    }

    // Test cJSON_DeleteItemFromObject
    cJSON_DeleteItemFromObject(json_object, key);

    // Test cJSON_ReplaceItemInObject
    cJSON *new_item = cJSON_CreateString("new_value");
    if (new_item) {
        if (!cJSON_ReplaceItemInObject(json_object, key, new_item)) {
            cJSON_Delete(new_item);
        }
    }

    // Test cJSON_HasObjectItem
    cJSON_bool has_item = cJSON_HasObjectItem(json_object, key);

    // Test cJSON_DeleteItemFromObjectCaseSensitive
    cJSON_DeleteItemFromObjectCaseSensitive(json_object, key);

    // Cleanup
    free(key);
    cJSON_Delete(json_object);

    return 0;
}