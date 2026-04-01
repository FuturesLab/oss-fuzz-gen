// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_GetStringValue at cJSON.c:99:22 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2533:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_CreateRaw at cJSON.c:2566:23 in cJSON.h
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

static void fuzz_cJSON_Parse(const uint8_t *data, size_t size) {
    // Ensure the input is null-terminated
    char *json_string = (char *)malloc(size + 1);
    if (json_string == NULL) {
        return;
    }
    memcpy(json_string, data, size);
    json_string[size] = '\0';

    cJSON *json = cJSON_Parse(json_string);
    if (json != NULL) {
        cJSON_Delete(json);
    }
    free(json_string);
}

static void fuzz_cJSON_GetStringValue(cJSON *json) {
    if (json == NULL) {
        return;
    }

    char *string_value = cJSON_GetStringValue(json);
    if (string_value != NULL) {
        // Use the string value in some way
    }
}

static void fuzz_cJSON_AddStringToObject(cJSON *json, const uint8_t *data, size_t size) {
    if (json == NULL || size == 0) {
        return;
    }

    // Ensure the input is null-terminated
    char *name = (char *)malloc(size + 1);
    if (name == NULL) {
        return;
    }
    memcpy(name, data, size);
    name[size] = '\0';

    cJSON *result = cJSON_AddStringToObject(json, name, "test_string");
    if (result != NULL) {
        // Use the result in some way
    }
    free(name);
}

static void fuzz_cJSON_CreateStringReference(const uint8_t *data, size_t size) {
    // Ensure the input is null-terminated
    char *string = (char *)malloc(size + 1);
    if (string == NULL) {
        return;
    }
    memcpy(string, data, size);
    string[size] = '\0';

    cJSON *json = cJSON_CreateStringReference(string);
    if (json != NULL) {
        cJSON_Delete(json);
    }
    free(string);
}

static void fuzz_cJSON_PrintUnformatted(cJSON *json) {
    if (json == NULL) {
        return;
    }

    char *unformatted = cJSON_PrintUnformatted(json);
    if (unformatted != NULL) {
        free(unformatted);
    }
}

static void fuzz_cJSON_CreateRaw(const uint8_t *data, size_t size) {
    // Ensure the input is null-terminated
    char *raw = (char *)malloc(size + 1);
    if (raw == NULL) {
        return;
    }
    memcpy(raw, data, size);
    raw[size] = '\0';

    cJSON *json = cJSON_CreateRaw(raw);
    if (json != NULL) {
        cJSON_Delete(json);
    }
    free(raw);
}

int LLVMFuzzerTestOneInput_44(const uint8_t *Data, size_t Size) {
    fuzz_cJSON_Parse(Data, Size);

    // Ensure the input is null-terminated for cJSON_Parse
    char *input_string = (char *)malloc(Size + 1);
    if (input_string == NULL) {
        return 0;
    }
    memcpy(input_string, Data, Size);
    input_string[Size] = '\0';

    cJSON *json = cJSON_Parse(input_string);
    fuzz_cJSON_GetStringValue(json);
    fuzz_cJSON_AddStringToObject(json, Data, Size);
    fuzz_cJSON_PrintUnformatted(json);
    if (json != NULL) {
        cJSON_Delete(json);
    }

    free(input_string);

    fuzz_cJSON_CreateStringReference(Data, Size);
    fuzz_cJSON_CreateRaw(Data, Size);

    return 0;
}