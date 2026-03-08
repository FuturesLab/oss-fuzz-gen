// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_IsNumber at cJSON.c:3007:26 in cJSON.h
// cJSON_IsString at cJSON.c:3017:26 in cJSON.h
// cJSON_IsArray at cJSON.c:3027:26 in cJSON.h
// cJSON_IsNull at cJSON.c:2997:26 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddItemReferenceToObject at cJSON.c:2125:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddObjectToObject at cJSON.c:2219:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

static cJSON* create_random_cjson(const uint8_t *Data, size_t Size) {
    cJSON *item = cJSON_CreateObject();
    if (Size > 0) {
        item->type = Data[0] % 6; // Randomly assign a type
        if (item->type == cJSON_Number && Size >= sizeof(double)) {
            memcpy(&(item->valuedouble), Data, sizeof(double));
        } else if (item->type == cJSON_String) {
            item->valuestring = (char*)malloc(Size + 1);
            if (item->valuestring) {
                memcpy(item->valuestring, Data, Size);
                item->valuestring[Size] = '\0';
            }
        }
    }
    return item;
}

int LLVMFuzzerTestOneInput_34(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    cJSON *item = create_random_cjson(Data, Size);
    if (!item) return 0;

    // Fuzz cJSON_IsNumber
    cJSON_bool isNumber = cJSON_IsNumber(item);

    // Fuzz cJSON_IsString
    cJSON_bool isString = cJSON_IsString(item);

    // Fuzz cJSON_IsArray
    cJSON_bool isArray = cJSON_IsArray(item);

    // Fuzz cJSON_IsNull
    cJSON_bool isNull = cJSON_IsNull(item);

    // Fuzz cJSON_AddItemReferenceToObject
    cJSON *object = cJSON_CreateObject();
    if (object) {
        cJSON_AddItemReferenceToObject(object, "key", item);
        cJSON_Delete(object);
    }

    // Fuzz cJSON_AddObjectToObject
    cJSON *parent = cJSON_CreateObject();
    if (parent) {
        cJSON *child = cJSON_AddObjectToObject(parent, "child");
        // Avoid deleting child separately as it is managed by parent
        cJSON_Delete(parent);
    }

    // Clean up
    if (item->type == cJSON_String && item->valuestring) {
        free(item->valuestring);
    }
    cJSON_Delete(item);

    return 0;
}