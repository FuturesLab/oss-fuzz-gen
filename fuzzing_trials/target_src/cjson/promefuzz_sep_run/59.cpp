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
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

static cJSON* create_cjson_from_input(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return NULL;
    }

    // Create a new cJSON object
    cJSON *item = cJSON_CreateObject();
    if (item == NULL) {
        return NULL;
    }

    // Use the data to set some properties
    item->type = Data[0] % 7; // Randomly assign a type based on the first byte
    if (Size > 1) {
        item->valueint = Data[1];
    }
    if (Size > 2) {
        item->valuedouble = (double)Data[2];
    }
    if (Size > 3) {
        item->valuestring = (char*)malloc(Size - 3 + 1);
        if (item->valuestring != NULL) {
            memcpy(item->valuestring, Data + 3, Size - 3);
            item->valuestring[Size - 3] = '\0';
        }
    }

    return item;
}

int LLVMFuzzerTestOneInput_59(const uint8_t *Data, size_t Size) {
    // Prepare the environment
    cJSON *item = create_cjson_from_input(Data, Size);
    if (item == NULL) {
        return 0;
    }

    // Invoke the target functions
    cJSON_bool isString = cJSON_IsString(item);
    cJSON_bool isTrue = cJSON_IsTrue(item);
    cJSON_bool isObject = cJSON_IsObject(item);
    cJSON_bool isNull = cJSON_IsNull(item);
    cJSON_bool isRaw = cJSON_IsRaw(item);
    cJSON_bool isFalse = cJSON_IsFalse(item);

    // Cleanup
    cJSON_Delete(item);

    return 0;
}