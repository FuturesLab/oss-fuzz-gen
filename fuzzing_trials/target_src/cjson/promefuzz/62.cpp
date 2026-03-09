// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_DeleteItemFromArray at cJSON.c:2289:20 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1926:23 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1926:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_ReplaceItemViaPointer at cJSON.c:2353:26 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_ReplaceItemInArray at cJSON.c:2402:26 in cJSON.h
// cJSON_CreateStringArray at cJSON.c:2726:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DetachItemFromArray at cJSON.c:2279:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
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

static void fuzz_cJSON_DeleteItemFromArray(cJSON *array) {
    int index = rand() % 10; // Random index for deletion
    cJSON_DeleteItemFromArray(array, index);
}

static void fuzz_cJSON_GetArrayItem(const cJSON *array) {
    int index = rand() % 10; // Random index for retrieval
    cJSON *item = cJSON_GetArrayItem(array, index);
    if (item) {
        // Do something with the item if needed
    }
}

static void fuzz_cJSON_ReplaceItemViaPointer(cJSON *array) {
    int index = rand() % 10;
    cJSON *item = cJSON_GetArrayItem(array, index);
    if (item) {
        cJSON *new_item = cJSON_CreateString("replacement");
        cJSON_ReplaceItemViaPointer(array, item, new_item);
    }
}

static void fuzz_cJSON_ReplaceItemInArray(cJSON *array) {
    int index = rand() % 10;
    cJSON *new_item = cJSON_CreateString("replacement");
    cJSON_ReplaceItemInArray(array, index, new_item);
}

static void fuzz_cJSON_CreateStringArray(const uint8_t *Data, size_t Size) {
    const char *strings[3] = {"string1", "string2", "string3"};
    cJSON *array = cJSON_CreateStringArray(strings, 3);
    if (array) {
        fuzz_cJSON_DeleteItemFromArray(array);
        fuzz_cJSON_GetArrayItem(array);
        fuzz_cJSON_ReplaceItemViaPointer(array);
        fuzz_cJSON_ReplaceItemInArray(array);
        cJSON_Delete(array);
    }
}

static void fuzz_cJSON_DetachItemFromArray(cJSON *array) {
    int index = rand() % 10;
    cJSON *detached_item = cJSON_DetachItemFromArray(array, index);
    if (detached_item) {
        cJSON_Delete(detached_item);
    }
}

int LLVMFuzzerTestOneInput_62(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    fuzz_cJSON_CreateStringArray(Data, Size);

    cJSON *array = cJSON_CreateArray();
    if (array) {
        for (int i = 0; i < 10; ++i) {
            cJSON_AddItemToArray(array, cJSON_CreateNumber(i));
        }

        fuzz_cJSON_DeleteItemFromArray(array);
        fuzz_cJSON_GetArrayItem(array);
        fuzz_cJSON_ReplaceItemViaPointer(array);
        fuzz_cJSON_ReplaceItemInArray(array);
        fuzz_cJSON_DetachItemFromArray(array);

        cJSON_Delete(array);
    }

    return 0;
}