// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_IsObject at cJSON.c:3037:26 in cJSON.h
// cJSON_IsString at cJSON.c:3017:26 in cJSON.h
// cJSON_IsBool at cJSON.c:2988:26 in cJSON.h
// cJSON_IsNull at cJSON.c:2997:26 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
// cJSON_IsFalse at cJSON.c:2967:26 in cJSON.h
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

static cJSON* create_random_cjson(const uint8_t *Data, size_t Size) {
    if (Size == 0) return NULL;

    cJSON *item = cJSON_CreateObject();
    if (item == NULL) return NULL;

    item->type = Data[0] % 7; // Random type based on first byte
    switch (item->type) {
        case cJSON_String:
            if (Size > 1) {
                item->valuestring = (char*)malloc(Size);
                if (item->valuestring != NULL) {
                    memcpy(item->valuestring, Data + 1, Size - 1);
                    item->valuestring[Size - 1] = '\0';
                }
            }
            break;
        case cJSON_Number:
            if (Size >= sizeof(double) + 1) {
                memcpy(&item->valuedouble, Data + 1, sizeof(double));
            }
            break;
        case cJSON_True:
        case cJSON_False:
        case cJSON_NULL:
        case cJSON_Object:
        case cJSON_Array:
            // No additional data needed for these types
            break;
    }
    return item;
}

static void free_cjson_item(cJSON *item) {
    if (item == NULL) return;
    if (item->type == cJSON_String && item->valuestring != NULL) {
        free(item->valuestring);
    }
    cJSON_Delete(item);
}

int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    cJSON *item = create_random_cjson(Data, Size);
    if (item == NULL) return 0;

    // Test the cJSON_IsObject function
    cJSON_IsObject(item);

    // Test the cJSON_IsString function
    cJSON_IsString(item);

    // Test the cJSON_IsBool function
    cJSON_IsBool(item);

    // Test the cJSON_IsNull function
    cJSON_IsNull(item);

    // Test the cJSON_IsTrue function
    cJSON_IsTrue(item);

    // Test the cJSON_IsFalse function
    cJSON_IsFalse(item);

    // Clean up
    free_cjson_item(item);
    return 0;
}