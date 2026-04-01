// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2183:22 in cJSON.h
// cJSON_AddBoolToObject at cJSON.c:2171:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2435:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_GetObjectItem at cJSON.c:1968:23 in cJSON.h
// cJSON_DetachItemFromObject at cJSON.c:2294:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_HasObjectItem at cJSON.c:1978:26 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2313:20 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2308:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

static cJSON *create_dummy_json_object() {
    cJSON *object = cJSON_CreateObject();
    cJSON_AddStringToObject(object, "key1", "value1");
    cJSON_AddNumberToObject(object, "key2", 42);
    cJSON_AddBoolToObject(object, "key3", 1);
    return object;
}

static char *extract_string(const uint8_t *Data, size_t Size) {
    if (Size == 0) return NULL;
    char *str = (char *)malloc(Size + 1);
    if (!str) return NULL;
    memcpy(str, Data, Size);
    str[Size] = '\0';
    return str;
}

int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cJSON *object = create_dummy_json_object();
    if (!object) return 0;

    char *key = extract_string(Data, Size);
    if (!key) {
        cJSON_Delete(object);
        return 0;
    }

    // Fuzz cJSON_ReplaceItemInObject
    cJSON *new_item = cJSON_CreateString("new_value");
    if (new_item) {
        if (!cJSON_ReplaceItemInObject(object, key, new_item)) {
            cJSON_Delete(new_item); // Clean up if replacement fails
        }
    }

    // Fuzz cJSON_GetObjectItem
    cJSON *item = cJSON_GetObjectItem(object, key);

    // Fuzz cJSON_DetachItemFromObject
    cJSON *detached_item = cJSON_DetachItemFromObject(object, key);
    if (detached_item) {
        cJSON_Delete(detached_item);
    }

    // Fuzz cJSON_HasObjectItem
    cJSON_bool has_item = cJSON_HasObjectItem(object, key);

    // Fuzz cJSON_DeleteItemFromObjectCaseSensitive
    cJSON_DeleteItemFromObjectCaseSensitive(object, key);

    // Fuzz cJSON_DeleteItemFromObject
    cJSON_DeleteItemFromObject(object, key);

    // Cleanup
    free(key);
    cJSON_Delete(object);

    return 0;
}