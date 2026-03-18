// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_DeleteItemFromArray at cJSON.c:2289:20 in cJSON.h
// cJSON_Duplicate at cJSON.c:2769:23 in cJSON.h
// cJSON_ReplaceItemViaPointer at cJSON.c:2353:26 in cJSON.h
// cJSON_ReplaceItemInArray at cJSON.c:2402:26 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_DetachItemFromArray at cJSON.c:2279:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_GetArraySize at cJSON.c:1884:19 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_GetArraySize at cJSON.c:1884:19 in cJSON.h
// cJSON_GetArraySize at cJSON.c:1884:19 in cJSON.h
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

static void fuzz_cJSON_DeleteItemFromArray(cJSON *array, int index) {
    cJSON_DeleteItemFromArray(array, index);
}

static cJSON* fuzz_cJSON_Duplicate(const cJSON *item, cJSON_bool recurse) {
    return cJSON_Duplicate(item, recurse);
}

static cJSON_bool fuzz_cJSON_ReplaceItemViaPointer(cJSON *parent, cJSON *item, cJSON *replacement) {
    return cJSON_ReplaceItemViaPointer(parent, item, replacement);
}

static cJSON_bool fuzz_cJSON_ReplaceItemInArray(cJSON *array, int index, cJSON *newitem) {
    return cJSON_ReplaceItemInArray(array, index, newitem);
}

static cJSON_bool fuzz_cJSON_AddItemToArray(cJSON *array, cJSON *item) {
    return cJSON_AddItemToArray(array, item);
}

static cJSON* fuzz_cJSON_DetachItemFromArray(cJSON *array, int index) {
    return cJSON_DetachItemFromArray(array, index);
}

int LLVMFuzzerTestOneInput_57(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a dummy JSON array
    cJSON *array = cJSON_CreateArray();
    cJSON *item1 = cJSON_CreateString("Item 1");
    cJSON *item2 = cJSON_CreateString("Item 2");
    cJSON *item3 = cJSON_CreateString("Item 3");

    // Add items to array
    fuzz_cJSON_AddItemToArray(array, item1);
    fuzz_cJSON_AddItemToArray(array, item2);
    fuzz_cJSON_AddItemToArray(array, item3);

    // Fuzz cJSON_DeleteItemFromArray
    int indexToDelete = Data[0] % cJSON_GetArraySize(array);
    fuzz_cJSON_DeleteItemFromArray(array, indexToDelete);

    // Fuzz cJSON_Duplicate
    cJSON *duplicate = fuzz_cJSON_Duplicate(array, 1);
    if (duplicate) {
        cJSON_Delete(duplicate);
    }

    // Fuzz cJSON_ReplaceItemViaPointer
    if (indexToDelete != 1) { // Ensure item2 is not deleted before replacing
        cJSON *replacementItem = cJSON_CreateString("Replacement Item");
        fuzz_cJSON_ReplaceItemViaPointer(array, item2, replacementItem);
    }

    // Fuzz cJSON_ReplaceItemInArray
    cJSON *newItem = cJSON_CreateString("New Item");
    fuzz_cJSON_ReplaceItemInArray(array, Data[0] % cJSON_GetArraySize(array), newItem);

    // Fuzz cJSON_DetachItemFromArray
    cJSON *detachedItem = fuzz_cJSON_DetachItemFromArray(array, Data[0] % cJSON_GetArraySize(array));
    if (detachedItem) {
        cJSON_Delete(detachedItem);
    }

    // Clean up
    cJSON_Delete(array);

    return 0;
}