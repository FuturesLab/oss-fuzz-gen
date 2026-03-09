// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_AddItemToObjectCS at cJSON.c:2110:26 in cJSON.h
// cJSON_AddItemReferenceToArray at cJSON.c:2115:26 in cJSON.h
// cJSON_AddItemReferenceToArray at cJSON.c:2115:26 in cJSON.h
// cJSON_AddItemReferenceToObject at cJSON.c:2125:26 in cJSON.h
// cJSON_AddItemReferenceToObject at cJSON.c:2125:26 in cJSON.h
// cJSON_DeleteItemFromArray at cJSON.c:2289:20 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2308:20 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2308:20 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2313:20 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2313:20 in cJSON.h
// cJSON_Minify at cJSON.c:2909:20 in cJSON.h
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

static cJSON* create_random_cjson_item(const uint8_t *Data, size_t Size) {
    if (Size == 0) return NULL;
    
    cJSON *item = cJSON_CreateObject();
    if (!item) return NULL;

    char *key = (char *)malloc(Size + 1);
    if (!key) {
        cJSON_Delete(item);
        return NULL;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';

    cJSON_AddStringToObject(item, key, "value");
    free(key);
    return item;
}

int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    cJSON *object1 = cJSON_CreateObject();
    cJSON *object2 = cJSON_CreateObject();
    cJSON *array = cJSON_CreateArray();

    if (!object1 || !object2 || !array) {
        cJSON_Delete(object1);
        cJSON_Delete(object2);
        cJSON_Delete(array);
        return 0;
    }

    cJSON *item1 = create_random_cjson_item(Data, Size / 2);
    cJSON *item2 = create_random_cjson_item(Data + Size / 2, Size - Size / 2);
    cJSON *item3 = create_random_cjson_item(Data, Size / 2);

    if (!item1 || !item2 || !item3) {
        cJSON_Delete(object1);
        cJSON_Delete(object2);
        cJSON_Delete(array);
        cJSON_Delete(item1);
        cJSON_Delete(item2);
        cJSON_Delete(item3);
        return 0;
    }

    cJSON_AddItemToObject(object1, "key1", item1);
    cJSON_AddItemToObject(object1, "key2", item2);
    cJSON_AddItemToObjectCS(object1, "key3", item3);

    cJSON_AddItemReferenceToArray(array, item1);
    cJSON_AddItemReferenceToArray(array, item2);
    cJSON_AddItemReferenceToObject(object2, "key1", item1);
    cJSON_AddItemReferenceToObject(object2, "key2", item2);

    cJSON_DeleteItemFromArray(array, 0);
    cJSON_DeleteItemFromObject(object1, "key1");
    cJSON_DeleteItemFromObject(object1, "key2");
    cJSON_DeleteItemFromObjectCaseSensitive(object2, "key1");
    cJSON_DeleteItemFromObjectCaseSensitive(object2, "key2");

    char json_string[] = "{\"sample\":\"data\"}";
    cJSON_Minify(json_string);

    cJSON_Delete(array);
    cJSON_Delete(object1);
    cJSON_Delete(object2);

    return 0;
}