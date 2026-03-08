// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_DetachItemFromObject at cJSON.c:2294:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DetachItemFromObjectCaseSensitive at cJSON.c:2301:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DeleteItemFromObject at cJSON.c:2308:20 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2435:26 in cJSON.h
// cJSON_HasObjectItem at cJSON.c:1978:26 in cJSON.h
// cJSON_DeleteItemFromObjectCaseSensitive at cJSON.c:2313:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "cJSON.h"

static cJSON* parse_json(const uint8_t *Data, size_t Size) {
    char *json_string = (char *)malloc(Size + 1);
    if (!json_string) return NULL;
    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';
    cJSON *json = cJSON_Parse(json_string);
    free(json_string);
    return json;
}

static void fuzz_detach_item_from_object(cJSON *json, const char *key) {
    cJSON *detached = cJSON_DetachItemFromObject(json, key);
    if (detached) {
        cJSON_Delete(detached);
    }
}

static void fuzz_detach_item_from_object_case_sensitive(cJSON *json, const char *key) {
    cJSON *detached = cJSON_DetachItemFromObjectCaseSensitive(json, key);
    if (detached) {
        cJSON_Delete(detached);
    }
}

static void fuzz_delete_item_from_object(cJSON *json, const char *key) {
    cJSON_DeleteItemFromObject(json, key);
}

static void fuzz_replace_item_in_object(cJSON *json, const char *key, cJSON *new_item) {
    cJSON_ReplaceItemInObject(json, key, new_item);
}

static void fuzz_has_object_item(cJSON *json, const char *key) {
    cJSON_HasObjectItem(json, key);
}

static void fuzz_delete_item_from_object_case_sensitive(cJSON *json, const char *key) {
    cJSON_DeleteItemFromObjectCaseSensitive(json, key);
}

int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    // Parse the input data into a JSON object
    cJSON *json = parse_json(Data, Size);
    if (!json) return 0;

    // Use the first byte for the key length
    size_t key_len = Data[0] % (Size - 1) + 1;
    char *key = (char *)malloc(key_len + 1);
    if (!key) {
        cJSON_Delete(json);
        return 0;
    }
    memcpy(key, Data + 1, key_len);
    key[key_len] = '\0';

    // Create a new JSON item for replacement
    cJSON *new_item = cJSON_CreateString("new_value");

    // Fuzz various functions
    fuzz_detach_item_from_object(json, key);
    fuzz_detach_item_from_object_case_sensitive(json, key);
    fuzz_delete_item_from_object(json, key);
    fuzz_replace_item_in_object(json, key, new_item);
    fuzz_has_object_item(json, key);
    fuzz_delete_item_from_object_case_sensitive(json, key);

    // Clean up
    cJSON_Delete(json);
    cJSON_Delete(new_item);
    free(key);

    return 0;
}