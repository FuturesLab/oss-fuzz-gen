// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2183:22 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateNull at cJSON.c:2446:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2435:26 in cJSON.h
// cJSON_AddItemReferenceToObject at cJSON.c:2125:26 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2183:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_PrintPreallocated at cJSON.c:1343:26 in cJSON.h
// cJSON_AddItemToObjectCS at cJSON.c:2110:26 in cJSON.h
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
    if (item == NULL) return NULL;

    // Populate the cJSON object with some random data
    cJSON_AddNumberToObject(item, "number", (double)(Data[0]));
    cJSON_AddStringToObject(item, "string", "fuzz");

    return item;
}

static char* create_random_string(const uint8_t *Data, size_t Size) {
    if (Size == 0) return NULL;
    char *str = (char*)malloc(Size + 1);
    if (str == NULL) return NULL;
    memcpy(str, Data, Size);
    str[Size] = '\0';
    return str;
}

int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
    // Create a base cJSON object
    cJSON *object = cJSON_CreateObject();
    if (object == NULL) return 0;

    // Create a new item to be added to the object
    cJSON *new_item = create_random_cjson_item(Data, Size);
    if (new_item == NULL) {
        cJSON_Delete(object);
        return 0;
    }

    // Create a random string key
    char *key = create_random_string(Data, Size);
    if (key == NULL) {
        cJSON_Delete(object);
        cJSON_Delete(new_item);
        return 0;
    }

    // Test cJSON_AddItemToObject to ensure the key exists in the object
    cJSON_AddItemToObject(object, key, cJSON_CreateNull());

    // Test cJSON_ReplaceItemInObject
    cJSON_ReplaceItemInObject(object, key, new_item);

    // Test cJSON_AddItemReferenceToObject
    cJSON_AddItemReferenceToObject(object, key, new_item);

    // Test cJSON_AddNumberToObject
    cJSON *number_item = cJSON_AddNumberToObject(object, key, 42.0);
    if (number_item == NULL) {
        cJSON_Delete(object);
        free(key);
        return 0;
    }

    // Test cJSON_AddItemToObject
    cJSON_AddItemToObject(object, key, create_random_cjson_item(Data, Size));

    // Prepare buffer for cJSON_PrintPreallocated
    size_t buffer_size = Size + 5;
    char *buffer = (char*)malloc(buffer_size);
    if (buffer != NULL) {
        // Test cJSON_PrintPreallocated
        cJSON_PrintPreallocated(object, buffer, (int)buffer_size, 1);
        free(buffer);
    }

    // Test cJSON_AddItemToObjectCS
    cJSON_AddItemToObjectCS(object, key, create_random_cjson_item(Data, Size));

    // Cleanup
    cJSON_Delete(object);
    free(key);

    return 0;
}