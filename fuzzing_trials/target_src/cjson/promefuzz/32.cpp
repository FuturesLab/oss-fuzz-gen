// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_DetachItemFromObjectCaseSensitive at cJSON.c:2301:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DetachItemFromObject at cJSON.c:2294:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2308:20 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2313:20 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2435:26 in cJSON.h
// cJSON_DetachItemViaPointer at cJSON.c:2243:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

static void fuzz_cJSON_DetachItemFromObjectCaseSensitive(cJSON *json, const char *key) {
    cJSON *detached_item = cJSON_DetachItemFromObjectCaseSensitive(json, key);
    if (detached_item) {
        cJSON_Delete(detached_item);
    }
}

static void fuzz_cJSON_DetachItemFromObject(cJSON *json, const char *key) {
    cJSON *detached_item = cJSON_DetachItemFromObject(json, key);
    if (detached_item) {
        cJSON_Delete(detached_item);
    }
}

static void fuzz_cJSON_DeleteItemFromObject(cJSON *json, const char *key) {
    cJSON_DeleteItemFromObject(json, key);
}

static void fuzz_cJSON_DeleteItemFromObjectCaseSensitive(cJSON *json, const char *key) {
    cJSON_DeleteItemFromObjectCaseSensitive(json, key);
}

static void fuzz_cJSON_ReplaceItemInObject(cJSON *json, const char *key, cJSON *new_item) {
    cJSON_ReplaceItemInObject(json, key, new_item);
}

static void fuzz_cJSON_DetachItemViaPointer(cJSON *parent, cJSON *item) {
    cJSON *detached_item = cJSON_DetachItemViaPointer(parent, item);
    if (detached_item) {
        cJSON_Delete(detached_item);
    }
}

int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a JSON object from the input data
    char *json_data = (char *)malloc(Size + 1);
    if (!json_data) return 0;
    memcpy(json_data, Data, Size);
    json_data[Size] = '\0';

    cJSON *json = cJSON_Parse(json_data);
    free(json_data);

    if (!json) return 0;

    // Use the first byte of data as a key
    char key[2] = {(char)Data[0], '\0'};

    // Fuzz the functions
    fuzz_cJSON_DetachItemFromObjectCaseSensitive(json, key);
    fuzz_cJSON_DetachItemFromObject(json, key);
    fuzz_cJSON_DeleteItemFromObject(json, key);
    fuzz_cJSON_DeleteItemFromObjectCaseSensitive(json, key);

    // Create a new item for replacing
    cJSON *new_item = cJSON_CreateString("new_value");
    if (new_item) {
        fuzz_cJSON_ReplaceItemInObject(json, key, new_item);
        cJSON_Delete(new_item);
    }

    // Fuzz DetachItemViaPointer with the first child
    if (json->child) {
        fuzz_cJSON_DetachItemViaPointer(json, json->child);
    }

    cJSON_Delete(json);

    return 0;
}