// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_AddItemReferenceToObject at cJSON.c:2125:26 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2435:26 in cJSON.h
// cJSON_AddItemToObjectCS at cJSON.c:2110:26 in cJSON.h
// cJSON_ReplaceItemInObjectCaseSensitive at cJSON.c:2440:26 in cJSON.h
// cJSON_HasObjectItem at cJSON.c:1978:26 in cJSON.h
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

static cJSON* create_random_cjson_item(const uint8_t *Data, size_t Size) {
    if (Size == 0) return NULL;

    cJSON *item = cJSON_CreateObject();
    if (!item) return NULL;

    // Randomly decide what to populate
    if (Size % 3 == 0) {
        item->type = cJSON_String;
        item->valuestring = (char *)malloc(Size + 1);
        if (item->valuestring) {
            memcpy(item->valuestring, Data, Size);
            item->valuestring[Size] = '\0';
        }
    } else if (Size % 3 == 1) {
        item->type = cJSON_Number;
        item->valuedouble = (double)(Data[0]);
    } else {
        item->type = cJSON_Object;
        item->child = create_random_cjson_item(Data, Size / 2);
    }

    return item;
}

int LLVMFuzzerTestOneInput_39(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Create a base JSON object
    cJSON *object = cJSON_CreateObject();
    if (!object) return 0;

    // Create a key and item based on input data
    char *key = (char *)malloc(Size + 1);
    if (!key) {
        cJSON_Delete(object);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';

    cJSON *item = create_random_cjson_item(Data, Size);
    if (!item) {
        free(key);
        cJSON_Delete(object);
        return 0;
    }

    // Fuzz the target API functions
    cJSON_AddItemToObject(object, key, item);
    cJSON_AddItemReferenceToObject(object, key, item);
    cJSON_ReplaceItemInObject(object, key, create_random_cjson_item(Data, Size / 2));
    cJSON_AddItemToObjectCS(object, key, create_random_cjson_item(Data, Size / 2));
    cJSON_ReplaceItemInObjectCaseSensitive(object, key, create_random_cjson_item(Data, Size / 2));
    cJSON_HasObjectItem(object, key);

    // Cleanup
    free(key);
    cJSON_Delete(object);

    return 0;
}