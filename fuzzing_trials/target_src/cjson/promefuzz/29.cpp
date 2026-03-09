// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_IsInvalid at cJSON.c:2957:26 in cJSON.h
// cJSON_IsString at cJSON.c:3017:26 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
// cJSON_IsObject at cJSON.c:3037:26 in cJSON.h
// cJSON_IsNull at cJSON.c:2997:26 in cJSON.h
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
#include <stdbool.h>
#include "cJSON.h"

static cJSON* parse_json(const uint8_t *Data, size_t Size) {
    char *json_string = (char *)malloc(Size + 1);
    if (!json_string) {
        return NULL;
    }
    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';
    
    cJSON *json = cJSON_Parse(json_string);
    free(json_string);
    return json;
}

int LLVMFuzzerTestOneInput_29(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    cJSON *json = parse_json(Data, Size);
    if (!json) {
        return 0;
    }

    // Invoke the target functions
    cJSON_IsInvalid(json);
    cJSON_IsString(json);
    cJSON_IsTrue(json);
    cJSON_IsObject(json);
    cJSON_IsNull(json);
    cJSON_IsFalse(json);

    cJSON_Delete(json);
    return 0;
}