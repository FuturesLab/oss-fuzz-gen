// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_IsObject at cJSON.c:3037:26 in cJSON.h
// cJSON_IsString at cJSON.c:3017:26 in cJSON.h
// cJSON_IsNull at cJSON.c:2997:26 in cJSON.h
// cJSON_IsInvalid at cJSON.c:2957:26 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
// cJSON_IsFalse at cJSON.c:2967:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
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
    char *json_data = (char *)malloc(Size + 1);
    if (json_data == NULL) {
        return NULL;
    }
    memcpy(json_data, Data, Size);
    json_data[Size] = '\0';

    cJSON *item = cJSON_Parse(json_data);
    free(json_data);
    return item;
}

int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    cJSON *item = create_cjson_from_input(Data, Size);
    if (item == NULL) {
        return 0;
    }

    // Test cJSON_IsObject
    cJSON_bool is_object = cJSON_IsObject(item);

    // Test cJSON_IsString
    cJSON_bool is_string = cJSON_IsString(item);

    // Test cJSON_IsNull
    cJSON_bool is_null = cJSON_IsNull(item);

    // Test cJSON_IsInvalid
    cJSON_bool is_invalid = cJSON_IsInvalid(item);

    // Test cJSON_IsTrue
    cJSON_bool is_true = cJSON_IsTrue(item);

    // Test cJSON_IsFalse
    cJSON_bool is_false = cJSON_IsFalse(item);

    // Cleanup
    cJSON_Delete(item);

    return 0;
}