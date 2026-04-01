// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_GetErrorPtr at cJSON.c:94:28 in cJSON.h
// cJSON_Print at cJSON.c:1302:22 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_PrintBuffered at cJSON.c:1312:22 in cJSON.h
// cJSON_Minify at cJSON.c:2909:20 in cJSON.h
// cJSON_Version at cJSON.c:124:27 in cJSON.h
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

int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Parse JSON data
    cJSON *json = parse_json(Data, Size);
    if (!json) {
        // Check for parsing error
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr) {
            // Handle the error pointer if needed
        }
        return 0;
    }

    // Test cJSON_Print
    char *printed_json = cJSON_Print(json);
    if (printed_json) {
        free(printed_json);
    }

    // Test cJSON_PrintUnformatted
    char *unformatted_json = cJSON_PrintUnformatted(json);
    if (unformatted_json) {
        free(unformatted_json);
    }

    // Test cJSON_PrintBuffered
    char *buffered_json = cJSON_PrintBuffered(json, 1024, 1);
    if (buffered_json) {
        free(buffered_json);
    }

    // Test cJSON_Minify
    char *json_string = (char *)malloc(Size + 1);
    if (json_string) {
        memcpy(json_string, Data, Size);
        json_string[Size] = '\0';
        cJSON_Minify(json_string);
        free(json_string);
    }

    // Test cJSON_Version
    const char *version = cJSON_Version();
    (void)version; // Suppress unused variable warning

    // Clean up
    cJSON_Delete(json);

    return 0;
}