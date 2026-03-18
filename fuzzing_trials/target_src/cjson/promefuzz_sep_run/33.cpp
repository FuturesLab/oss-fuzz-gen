// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_IsInvalid at cJSON.c:2957:26 in cJSON.h
// cJSON_IsNumber at cJSON.c:3007:26 in cJSON.h
// cJSON_IsString at cJSON.c:3017:26 in cJSON.h
// cJSON_IsObject at cJSON.c:3037:26 in cJSON.h
// cJSON_IsNull at cJSON.c:2997:26 in cJSON.h
// cJSON_IsFalse at cJSON.c:2967:26 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

static cJSON* create_cjson_from_data(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cJSON)) {
        return NULL;
    }

    cJSON *item = (cJSON *)malloc(sizeof(cJSON));
    if (!item) {
        return NULL;
    }

    memcpy(item, Data, sizeof(cJSON));

    if (Size > sizeof(cJSON)) {
        size_t string_size = Size - sizeof(cJSON);
        item->valuestring = (char *)malloc(string_size + 1);
        if (item->valuestring) {
            memcpy(item->valuestring, Data + sizeof(cJSON), string_size);
            item->valuestring[string_size] = '\0';
        }
    } else {
        item->valuestring = NULL;
    }

    return item;
}

static void free_cjson(cJSON *item) {
    if (item) {
        if (item->valuestring) {
            free(item->valuestring);
        }
        free(item);
    }
}

int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    cJSON *item = create_cjson_from_data(Data, Size);
    if (!item) {
        return 0;
    }

    // Invoke the target functions
    cJSON_bool isInvalid = cJSON_IsInvalid(item);
    cJSON_bool isNumber = cJSON_IsNumber(item);
    cJSON_bool isString = cJSON_IsString(item);
    cJSON_bool isObject = cJSON_IsObject(item);
    cJSON_bool isNull = cJSON_IsNull(item);
    cJSON_bool isFalse = cJSON_IsFalse(item);

    // Use the results to explore different states
    if (isInvalid || isNumber || isString || isObject || isNull || isFalse) {
        // Potentially perform additional actions based on results
    }

    // Clean up
    free_cjson(item);

    return 0;
}