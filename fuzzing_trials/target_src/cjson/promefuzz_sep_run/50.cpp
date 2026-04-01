// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_IsString at cJSON.c:3017:26 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
// cJSON_IsObject at cJSON.c:3037:26 in cJSON.h
// cJSON_IsNull at cJSON.c:2997:26 in cJSON.h
// cJSON_IsRaw at cJSON.c:3047:26 in cJSON.h
// cJSON_IsFalse at cJSON.c:2967:26 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cJSON.h"

static cJSON* create_cjson_from_input(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return NULL;
    }

    cJSON *item = (cJSON *)malloc(sizeof(cJSON));
    if (!item) {
        return NULL;
    }
    memset(item, 0, sizeof(cJSON));

    // Arbitrarily decide type based on the first byte of input
    switch (Data[0] % 6) {
        case 0:
            item->type = cJSON_String;
            item->valuestring = (char *)malloc(Size + 1);
            if (item->valuestring) {
                memcpy(item->valuestring, Data, Size);
                item->valuestring[Size] = '\0';
            }
            break;
        case 1:
            item->type = cJSON_True;
            break;
        case 2:
            item->type = cJSON_Object;
            break;
        case 3:
            item->type = cJSON_NULL;
            break;
        case 4:
            item->type = cJSON_Raw;
            item->valuestring = (char *)malloc(Size + 1);
            if (item->valuestring) {
                memcpy(item->valuestring, Data, Size);
                item->valuestring[Size] = '\0';
            }
            break;
        case 5:
            item->type = cJSON_False;
            break;
        default:
            free(item);
            return NULL;
    }

    return item;
}

int LLVMFuzzerTestOneInput_50(const uint8_t *Data, size_t Size) {
    cJSON *item = create_cjson_from_input(Data, Size);
    if (!item) {
        return 0;
    }

    // Test the various cJSON_Is* functions
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
    free(item);

    return 0;
}