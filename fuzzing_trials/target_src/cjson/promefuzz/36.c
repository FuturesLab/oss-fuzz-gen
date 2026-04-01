// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_DetachItemViaPointer at cJSON.c:2243:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2435:26 in cJSON.h
// cJSON_ReplaceItemViaPointer at cJSON.c:2353:26 in cJSON.h
// cJSON_ReplaceItemInObjectCaseSensitive at cJSON.c:2440:26 in cJSON.h
// cJSON_CreateStringArray at cJSON.c:2726:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_ReplaceItemInArray at cJSON.c:2402:26 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "cJSON.h"

static void test_cJSON_DetachItemViaPointer(cJSON *parent, cJSON *item) {
    cJSON *detached = cJSON_DetachItemViaPointer(parent, item);
    if (detached) {
        cJSON_Delete(detached);
    }
}

static void test_cJSON_ReplaceItemInObject(cJSON *object, const char *key, cJSON *newitem) {
    cJSON_ReplaceItemInObject(object, key, newitem);
}

static void test_cJSON_ReplaceItemViaPointer(cJSON *parent, cJSON *item, cJSON *replacement) {
    cJSON_ReplaceItemViaPointer(parent, item, replacement);
}

static void test_cJSON_ReplaceItemInObjectCaseSensitive(cJSON *object, const char *key, cJSON *newitem) {
    cJSON_ReplaceItemInObjectCaseSensitive(object, key, newitem);
}

static void test_cJSON_CreateStringArray(const char *const *strings, int count) {
    cJSON *array = cJSON_CreateStringArray(strings, count);
    if (array) {
        cJSON_Delete(array);
    }
}

static void test_cJSON_ReplaceItemInArray(cJSON *array, int which, cJSON *newitem) {
    cJSON_ReplaceItemInArray(array, which, newitem);
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Ensure the input is null-terminated for cJSON_Parse
    char *input = (char *)malloc(Size + 1);
    if (!input) return 0;

    memcpy(input, Data, Size);
    input[Size] = '\0';

    cJSON *json = cJSON_Parse(input);
    free(input);

    if (!json) return 0;

    cJSON *newitem = cJSON_CreateString("new_value");
    if (!newitem) {
        cJSON_Delete(json);
        return 0;
    }

    // Testing cJSON_DetachItemViaPointer
    test_cJSON_DetachItemViaPointer(json, json->child);

    // Testing cJSON_ReplaceItemInObject
    test_cJSON_ReplaceItemInObject(json, "key", newitem);

    // Testing cJSON_ReplaceItemViaPointer
    test_cJSON_ReplaceItemViaPointer(json, json->child, newitem);

    // Testing cJSON_ReplaceItemInObjectCaseSensitive
    test_cJSON_ReplaceItemInObjectCaseSensitive(json, "key", newitem);

    // Testing cJSON_CreateStringArray
    const char *strings[] = {"one", "two", "three"};
    test_cJSON_CreateStringArray(strings, 3);

    // Testing cJSON_ReplaceItemInArray
    test_cJSON_ReplaceItemInArray(json, 0, newitem);

    cJSON_Delete(json);
    cJSON_Delete(newitem);

    return 0;
}