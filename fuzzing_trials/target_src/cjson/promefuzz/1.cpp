// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_ParseWithOpts at cJSON.c:1126:23 in cJSON.h
// cJSON_PrintBuffered at cJSON.c:1312:22 in cJSON.h
// cJSON_Print at cJSON.c:1302:22 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Minify at cJSON.c:2909:20 in cJSON.h
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

int LLVMFuzzerTestOneInput_1(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Ensure the input data is null-terminated
    char *json_data = (char *)malloc(Size + 1);
    if (!json_data) {
        return 0;
    }
    memcpy(json_data, Data, Size);
    json_data[Size] = '\0';

    // Parse the JSON data
    const char *parse_end = NULL;
    cJSON *json = cJSON_ParseWithOpts(json_data, &parse_end, 0);

    if (json) {
        // Print buffered
        char *buffered_output = cJSON_PrintBuffered(json, 1024, 1);
        if (buffered_output) {
            free(buffered_output);
        }

        // Print formatted
        char *formatted_output = cJSON_Print(json);
        if (formatted_output) {
            free(formatted_output);
        }

        // Print unformatted
        char *unformatted_output = cJSON_PrintUnformatted(json);
        if (unformatted_output) {
            free(unformatted_output);
        }

        // Minify the JSON data
        cJSON_Minify(json_data);

        // Clean up the cJSON object
        cJSON_Delete(json);
    }

    free(json_data);
    return 0;
}