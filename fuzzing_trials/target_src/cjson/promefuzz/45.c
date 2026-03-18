// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_IsRaw at cJSON.c:3047:26 in cJSON.h
// cJSON_IsObject at cJSON.c:3037:26 in cJSON.h
// cJSON_IsString at cJSON.c:3017:26 in cJSON.h
// cJSON_IsNull at cJSON.c:2997:26 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
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

static cJSON* create_cjson_from_input(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return NULL;
    }

    // Allocate memory for cJSON object
    cJSON *item = (cJSON *)malloc(sizeof(cJSON));
    if (!item) {
        return NULL;
    }

    // Initialize the cJSON object with some default values
    item->next = NULL;
    item->prev = NULL;
    item->child = NULL;
    item->type = Data[0] % 7; // Random type based on input data
    item->valuestring = NULL;
    item->valueint = 0;
    item->valuedouble = 0.0;
    item->string = NULL;

    // Set valuestring if the type is cJSON_String or cJSON_Raw
    if (item->type == cJSON_String || item->type == cJSON_Raw) {
        item->valuestring = (char *)malloc(Size + 1);
        if (item->valuestring) {
            memcpy(item->valuestring, Data, Size);
            item->valuestring[Size] = '\0';
        }
    }

    return item;
}

static void cleanup_cjson(cJSON *item) {
    if (item) {
        if (item->valuestring) {
            free(item->valuestring);
        }
        free(item);
    }
}

int LLVMFuzzerTestOneInput_45(const uint8_t *Data, size_t Size) {
    cJSON *item = create_cjson_from_input(Data, Size);
    if (!item) {
        return 0;
    }

    // Invoke the target functions with the created cJSON object
    cJSON_bool isRaw = cJSON_IsRaw(item);
    cJSON_bool isObject = cJSON_IsObject(item);
    cJSON_bool isString = cJSON_IsString(item);
    cJSON_bool isNull = cJSON_IsNull(item);
    cJSON_bool isTrue = cJSON_IsTrue(item);
    cJSON_bool isFalse = cJSON_IsFalse(item);

    // Use the return values to prevent compiler optimizations
    volatile cJSON_bool result = isRaw | isObject | isString | isNull | isTrue | isFalse;

    cleanup_cjson(item);
    return 0;
}