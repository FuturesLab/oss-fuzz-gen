// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_GetArraySize at cJSON.c:1884:19 in cJSON.h
// cJSON_DetachItemFromArray at cJSON.c:2279:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_DeleteItemFromArray at cJSON.c:2289:20 in cJSON.h
// cJSON_InsertItemInArray at cJSON.c:2319:26 in cJSON.h
// cJSON_IsArray at cJSON.c:3027:26 in cJSON.h
// cJSON_CreateNull at cJSON.c:2446:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
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

static cJSON* create_random_cJSON_item(const uint8_t *Data, size_t Size) {
    if (Size == 0) return NULL;

    cJSON *item = cJSON_CreateObject();
    if (item == NULL) return NULL;

    // Randomly decide if the item will be an array or not
    if (Data[0] % 2 == 0) {
        cJSON_AddItemToObject(item, "array", cJSON_CreateArray());
    } else {
        cJSON_AddItemToObject(item, "value", cJSON_CreateNumber(Data[0]));
    }
    return item;
}

static cJSON* create_random_cJSON_array(const uint8_t *Data, size_t Size) {
    cJSON *array = cJSON_CreateArray();
    if (array == NULL) return NULL;

    for (size_t i = 0; i < Size; ++i) {
        cJSON *item = create_random_cJSON_item(Data + i, Size - i);
        if (item != NULL) {
            cJSON_AddItemToArray(array, item);
        }
    }
    return array;
}

int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    cJSON *array = create_random_cJSON_array(Data, Size);
    if (array == NULL) return 0;

    int array_size = cJSON_GetArraySize(array);
    if (array_size > 0) {
        int index = Data[0] % array_size;

        cJSON *detached_item = cJSON_DetachItemFromArray(array, index);
        if (detached_item != NULL) {
            cJSON_Delete(detached_item);
        }

        cJSON_DeleteItemFromArray(array, index);
    }

    cJSON *new_item = create_random_cJSON_item(Data, Size);
    if (new_item != NULL) {
        cJSON_InsertItemInArray(array, 0, new_item);
    }

    if (cJSON_IsArray(array)) {
        cJSON_AddItemToArray(array, cJSON_CreateNull());
    }

    cJSON_Delete(array);
    return 0;
}