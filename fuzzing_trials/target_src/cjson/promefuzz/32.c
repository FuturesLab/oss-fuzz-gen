// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_IsObject at cJSON.c:3037:26 in cJSON.h
// cJSON_IsString at cJSON.c:3017:26 in cJSON.h
// cJSON_IsBool at cJSON.c:2988:26 in cJSON.h
// cJSON_IsNull at cJSON.c:2997:26 in cJSON.h
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

static cJSON* parse_json(const uint8_t *Data, size_t Size) {
    // Create a null-terminated string from the data
    char *json_data = (char *)malloc(Size + 1);
    if (json_data == NULL) {
        return NULL;
    }
    memcpy(json_data, Data, Size);
    json_data[Size] = '\0';

    // Parse the JSON data
    cJSON *json = cJSON_Parse(json_data);
    free(json_data);
    return json;
}

int LLVMFuzzerTestOneInput_32(const uint8_t *Data, size_t Size) {
    // Parse input data into a cJSON structure
    cJSON *json = parse_json(Data, Size);
    if (json == NULL) {
        return 0; // If parsing fails, exit early
    }

    // Test cJSON_IsObject
    cJSON_bool is_object = cJSON_IsObject(json);

    // Test cJSON_IsString
    cJSON_bool is_string = cJSON_IsString(json);

    // Test cJSON_IsBool
    cJSON_bool is_bool = cJSON_IsBool(json);

    // Test cJSON_IsNull
    cJSON_bool is_null = cJSON_IsNull(json);

    // Test cJSON_IsTrue
    cJSON_bool is_true = cJSON_IsTrue(json);

    // Test cJSON_IsFalse
    cJSON_bool is_false = cJSON_IsFalse(json);

    // Clean up
    cJSON_Delete(json);

    return 0;
}