// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_GetStringValue at cJSON.c:99:22 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2533:23 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateRaw at cJSON.c:2566:23 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
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

static void fuzz_cJSON_Parse(const uint8_t *Data, size_t Size) {
    // Ensure the input data is null-terminated
    char *json_string = (char *)malloc(Size + 1);
    if (json_string == NULL) return;
    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';

    cJSON *json = cJSON_Parse(json_string);
    if (json != NULL) {
        // Use cJSON_GetStringValue to retrieve a string value
        char *string_value = cJSON_GetStringValue(json);
        if (string_value != NULL) {
            // Do something with string_value if needed
        }

        // Use cJSON_AddStringToObject to add a new string item
        cJSON *new_item = cJSON_AddStringToObject(json, "new_key", "new_value");
        if (new_item != NULL) {
            // Do something with new_item if needed
        }

        // Use cJSON_PrintUnformatted to get a compact string representation
        char *unformatted = cJSON_PrintUnformatted(json);
        if (unformatted != NULL) {
            // Do something with unformatted if needed
            free(unformatted);
        }

        cJSON_Delete(json);
    }

    free(json_string);
}

static void fuzz_cJSON_CreateStringReference(const uint8_t *Data, size_t Size) {
    // Create a string reference from the input data
    char *string_ref = (char *)malloc(Size + 1);
    if (string_ref == NULL) return;
    memcpy(string_ref, Data, Size);
    string_ref[Size] = '\0';

    cJSON *string_json = cJSON_CreateStringReference(string_ref);
    if (string_json != NULL) {
        // Use cJSON_PrintUnformatted to get a compact string representation
        char *unformatted = cJSON_PrintUnformatted(string_json);
        if (unformatted != NULL) {
            // Do something with unformatted if needed
            free(unformatted);
        }

        cJSON_Delete(string_json);
    }

    free(string_ref);
}

static void fuzz_cJSON_CreateRaw(const uint8_t *Data, size_t Size) {
    // Create a raw JSON item from the input data
    char *raw_string = (char *)malloc(Size + 1);
    if (raw_string == NULL) return;
    memcpy(raw_string, Data, Size);
    raw_string[Size] = '\0';

    cJSON *raw_json = cJSON_CreateRaw(raw_string);
    if (raw_json != NULL) {
        // Use cJSON_PrintUnformatted to get a compact string representation
        char *unformatted = cJSON_PrintUnformatted(raw_json);
        if (unformatted != NULL) {
            // Do something with unformatted if needed
            free(unformatted);
        }

        cJSON_Delete(raw_json);
    }

    free(raw_string);
}

int LLVMFuzzerTestOneInput_51(const uint8_t *Data, size_t Size) {
    fuzz_cJSON_Parse(Data, Size);
    fuzz_cJSON_CreateStringReference(Data, Size);
    fuzz_cJSON_CreateRaw(Data, Size);
    return 0;
}