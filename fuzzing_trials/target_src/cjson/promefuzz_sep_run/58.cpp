// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_Print at cJSON.c:1302:22 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_GetErrorPtr at cJSON.c:94:28 in cJSON.h
// cJSON_Version at cJSON.c:124:27 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
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

static cJSON* create_sample_json_object() {
    cJSON *object = cJSON_CreateObject();
    if (object) {
        cJSON_AddStringToObject(object, "sample_key", "sample_value");
    }
    return object;
}

int LLVMFuzzerTestOneInput_58(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Ensure null-termination for string operations
    char *input = (char *)malloc(Size + 1);
    if (!input) return 0;
    memcpy(input, Data, Size);
    input[Size] = '\0';

    // Test cJSON_Parse
    cJSON *parsed_json = cJSON_Parse(input);
    if (parsed_json) {
        // Test cJSON_Print
        char *printed_json = cJSON_Print(parsed_json);
        if (printed_json) {
            free(printed_json);
        }

        // Test cJSON_PrintUnformatted
        char *unformatted_json = cJSON_PrintUnformatted(parsed_json);
        if (unformatted_json) {
            free(unformatted_json);
        }

        cJSON_Delete(parsed_json);
    } else {
        // Test cJSON_GetErrorPtr
        const char *error_ptr = cJSON_GetErrorPtr();
        (void)error_ptr; // Avoid unused variable warning
    }

    // Test cJSON_Version
    const char *version = cJSON_Version();
    (void)version; // Avoid unused variable warning

    // Test cJSON_AddStringToObject
    cJSON *json_object = create_sample_json_object();
    if (json_object) {
        cJSON_AddStringToObject(json_object, "fuzz_key", input);
        cJSON_Delete(json_object);
    }

    free(input);
    return 0;
}