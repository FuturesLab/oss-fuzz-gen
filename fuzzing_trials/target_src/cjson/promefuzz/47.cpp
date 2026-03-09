// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_GetStringValue at cJSON.c:99:22 in cJSON.h
// cJSON_CreateRaw at cJSON.c:2566:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2533:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
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

static void handle_cJSON_AddStringToObject(cJSON *object, const uint8_t *Data, size_t Size) {
    if (Size < 3) return; // Ensure there are enough bytes for a name and a string
    size_t name_length = Data[0] % (Size - 2); // Length of the name, leaving space for null terminator
    const char *name = (const char *)(Data + 1);
    const char *string = (const char *)(Data + 1 + name_length);

    // Ensure null termination
    char *name_buf = (char *)malloc(name_length + 1);
    char *string_buf = (char *)malloc(Size - 1 - name_length + 1);
    if (!name_buf || !string_buf) {
        free(name_buf);
        free(string_buf);
        return;
    }
    memcpy(name_buf, name, name_length);
    name_buf[name_length] = '\0';
    memcpy(string_buf, string, Size - 1 - name_length);
    string_buf[Size - 1 - name_length] = '\0';

    cJSON *result = cJSON_AddStringToObject(object, name_buf, string_buf);
    if (result) {
        // Do something with result if needed
    }

    free(name_buf);
    free(string_buf);
}

static void handle_cJSON_GetStringValue(const cJSON *item) {
    char *value = cJSON_GetStringValue(item);
    if (value) {
        // Do something with value if needed
    }
}

static void handle_cJSON_CreateRaw(const uint8_t *Data, size_t Size) {
    char *raw_data = (char *)malloc(Size + 1);
    if (!raw_data) return;
    memcpy(raw_data, Data, Size);
    raw_data[Size] = '\0';

    cJSON *raw_item = cJSON_CreateRaw(raw_data);
    if (raw_item) {
        // Do something with raw_item if needed
        cJSON_Delete(raw_item);
    }
    free(raw_data);
}

static void handle_cJSON_PrintUnformatted(const cJSON *item) {
    char *unformatted = cJSON_PrintUnformatted(item);
    if (unformatted) {
        // Do something with unformatted if needed
        free(unformatted);
    }
}

static void handle_cJSON_CreateStringReference(const uint8_t *Data, size_t Size) {
    char *string_ref = (char *)malloc(Size + 1);
    if (!string_ref) return;
    memcpy(string_ref, Data, Size);
    string_ref[Size] = '\0';

    cJSON *string_item = cJSON_CreateStringReference(string_ref);
    if (string_item) {
        // Do something with string_item if needed
        cJSON_Delete(string_item);
    }
    free(string_ref);
}

static void handle_cJSON_Parse(const uint8_t *Data, size_t Size) {
    char *json_data = (char *)malloc(Size + 1);
    if (!json_data) return;
    memcpy(json_data, Data, Size);
    json_data[Size] = '\0';

    cJSON *parsed_item = cJSON_Parse(json_data);
    if (parsed_item) {
        // Do something with parsed_item if needed
        cJSON_Delete(parsed_item);
    }
    free(json_data);
}

int LLVMFuzzerTestOneInput_47(const uint8_t *Data, size_t Size) {
    cJSON *object = cJSON_CreateObject();

    if (object) {
        handle_cJSON_AddStringToObject(object, Data, Size);
        handle_cJSON_GetStringValue(object);
        handle_cJSON_PrintUnformatted(object);
        cJSON_Delete(object);
    }

    handle_cJSON_CreateRaw(Data, Size);
    handle_cJSON_CreateStringReference(Data, Size);
    handle_cJSON_Parse(Data, Size);

    return 0;
}