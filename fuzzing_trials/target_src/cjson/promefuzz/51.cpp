// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_IsString at cJSON.c:3017:26 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
// cJSON_IsObject at cJSON.c:3037:26 in cJSON.h
// cJSON_IsNull at cJSON.c:2997:26 in cJSON.h
// cJSON_IsRaw at cJSON.c:3047:26 in cJSON.h
// cJSON_IsFalse at cJSON.c:2967:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "cJSON.h"

static cJSON* create_cjson_item(const uint8_t *Data, size_t Size) {
    if (Size == 0) return NULL;

    cJSON *item = cJSON_CreateObject();
    if (!item) return NULL;

    item->type = Data[0] % 7; // Randomly choose a type
    if (item->type == cJSON_String || item->type == cJSON_Raw) {
        item->valuestring = (char *)malloc(Size + 1);
        if (item->valuestring) {
            memcpy(item->valuestring, Data, Size);
            item->valuestring[Size] = '\0';
        }
    } else if (item->type == cJSON_Number) {
        item->valuedouble = (double)Data[0];
    } else if (item->type == cJSON_True) {
        item->valueint = 1;
    } else if (item->type == cJSON_False) {
        item->valueint = 0;
    } else if (item->type == cJSON_NULL) {
        // No additional data needed
    }

    return item;
}

int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    cJSON *item = create_cjson_item(Data, Size);
    if (!item) return 0;

    // Test the cJSON_Is* functions
    cJSON_bool isString = cJSON_IsString(item);
    cJSON_bool isTrue = cJSON_IsTrue(item);
    cJSON_bool isObject = cJSON_IsObject(item);
    cJSON_bool isNull = cJSON_IsNull(item);
    cJSON_bool isRaw = cJSON_IsRaw(item);
    cJSON_bool isFalse = cJSON_IsFalse(item);

    // Cleanup
    if (item->valuestring) {
        free(item->valuestring);
    }
    cJSON_Delete(item);

    return 0;
}