// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2183:22 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemReferenceToObject at cJSON.c:2125:26 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2435:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObjectCS at cJSON.c:2110:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_ReplaceItemInObjectCaseSensitive at cJSON.c:2440:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_HasObjectItem at cJSON.c:1978:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

static cJSON *generate_random_cjson() {
    cJSON *item = cJSON_CreateObject();
    if (!item) {
        return NULL;
    }
    // Add a random integer
    cJSON_AddNumberToObject(item, "random_number", rand());
    // Add a random string
    cJSON_AddStringToObject(item, "random_string", "fuzz");
    return item;
}

int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Prepare a JSON object to work with
    cJSON *json_object = cJSON_CreateObject();
    if (!json_object) return 0;

    // Use the first byte to determine which function to test
    uint8_t choice = Data[0];
    const char *key = "key";
    cJSON *item = generate_random_cjson();
    if (!item) {
        cJSON_Delete(json_object);
        return 0;
    }

    cJSON_bool result = 0;
    switch (choice % 6) {
        case 0:
            // Test cJSON_AddItemToObject
            result = cJSON_AddItemToObject(json_object, key, item);
            if (!result) {
                cJSON_Delete(item);
            }
            break;
        case 1:
            // Test cJSON_AddItemReferenceToObject
            result = cJSON_AddItemReferenceToObject(json_object, key, item);
            break;
        case 2:
            // Test cJSON_ReplaceItemInObject
            result = cJSON_ReplaceItemInObject(json_object, key, item);
            if (!result) {
                cJSON_Delete(item);
            }
            break;
        case 3:
            // Test cJSON_AddItemToObjectCS
            result = cJSON_AddItemToObjectCS(json_object, key, item);
            if (!result) {
                cJSON_Delete(item);
            }
            break;
        case 4:
            // Test cJSON_ReplaceItemInObjectCaseSensitive
            result = cJSON_ReplaceItemInObjectCaseSensitive(json_object, key, item);
            if (!result) {
                cJSON_Delete(item);
            }
            break;
        case 5:
            // Test cJSON_HasObjectItem
            result = cJSON_HasObjectItem(json_object, key);
            cJSON_Delete(item);
            break;
    }

    // Cleanup
    cJSON_Delete(json_object);
    
    return 0;
}