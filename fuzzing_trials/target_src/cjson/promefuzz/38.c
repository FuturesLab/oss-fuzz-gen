// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2183:22 in cJSON.h
// cJSON_Print at cJSON.c:1302:22 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2435:26 in cJSON.h
// cJSON_DetachItemFromObjectCaseSensitive at cJSON.c:2301:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2313:20 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2308:20 in cJSON.h
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

static cJSON* create_sample_json() {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "name", "example");
    cJSON_AddNumberToObject(root, "value", 42);
    return root;
}

int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a sample JSON object
    cJSON *json = create_sample_json();
    if (json == NULL) return 0;

    // cJSON_Print
    char *printed_json = cJSON_Print(json);
    if (printed_json != NULL) {
        free(printed_json);
    }

    // cJSON_PrintUnformatted
    char *unformatted_json = cJSON_PrintUnformatted(json);
    if (unformatted_json != NULL) {
        free(unformatted_json);
    }

    // Prepare a key and new item for replacement
    char *key = "name";

    // Ensure the data is null-terminated before using it as a string
    char *safe_data = (char *)malloc(Size + 1);
    if (safe_data == NULL) {
        cJSON_Delete(json);
        return 0;
    }
    memcpy(safe_data, Data, Size);
    safe_data[Size] = '\0';

    cJSON *new_item = cJSON_CreateString(safe_data);

    // cJSON_ReplaceItemInObject
    cJSON_ReplaceItemInObject(json, key, new_item);

    // cJSON_DetachItemFromObjectCaseSensitive
    cJSON *detached_item = cJSON_DetachItemFromObjectCaseSensitive(json, key);
    if (detached_item != NULL) {
        cJSON_Delete(detached_item);
    }

    // cJSON_DeleteItemFromObjectCaseSensitive
    cJSON_DeleteItemFromObjectCaseSensitive(json, key);

    // cJSON_DeleteItemFromObject
    cJSON_DeleteItemFromObject(json, key);

    // Cleanup
    free(safe_data);
    cJSON_Delete(json);
    return 0;
}