// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateStringArray at cJSON.c:2726:23 in cJSON.h
// cJSON_DeleteItemFromArray at cJSON.c:2289:20 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1926:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_ReplaceItemInArray at cJSON.c:2402:26 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1926:23 in cJSON.h
// cJSON_ReplaceItemViaPointer at cJSON.c:2353:26 in cJSON.h
// cJSON_DetachItemFromArray at cJSON.c:2279:23 in cJSON.h
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

static void safe_free(void *ptr) {
    if (ptr) {
        free(ptr);
    }
}

int LLVMFuzzerTestOneInput_53(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Prepare a dummy string array for cJSON_CreateStringArray
    const char *dummy_strings[] = {"string1", "string2", "string3"};
    int dummy_count = sizeof(dummy_strings) / sizeof(dummy_strings[0]);

    // Create a JSON array using cJSON_CreateStringArray
    cJSON *json_array = cJSON_CreateStringArray(dummy_strings, dummy_count);
    if (!json_array) {
        return 0;
    }

    // Use the data as an index
    int index = Data[0] % dummy_count;

    // Test cJSON_DeleteItemFromArray
    cJSON_DeleteItemFromArray(json_array, index);

    // Test cJSON_GetArrayItem
    cJSON *item = cJSON_GetArrayItem(json_array, index);

    // Create a replacement item
    cJSON *replacement_item = cJSON_CreateString("replacement");
    if (replacement_item) {
        // Test cJSON_ReplaceItemInArray
        cJSON_ReplaceItemInArray(json_array, index, replacement_item);

        // Test cJSON_ReplaceItemViaPointer
        // Ensure the item has not been deleted before replacing
        item = cJSON_GetArrayItem(json_array, index);
        if (item && item != replacement_item) {
            cJSON_ReplaceItemViaPointer(json_array, item, replacement_item);
        }
    }

    // Test cJSON_DetachItemFromArray
    cJSON *detached_item = cJSON_DetachItemFromArray(json_array, index);
    if (detached_item) {
        cJSON_Delete(detached_item);
    }

    // Clean up
    cJSON_Delete(json_array);

    return 0;
}