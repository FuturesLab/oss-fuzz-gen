// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_Print at cJSON.c:1302:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_GetErrorPtr at cJSON.c:94:28 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Version at cJSON.c:124:27 in cJSON.h
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

static void fuzz_cJSON_AddStringToObject(const uint8_t *Data, size_t Size) {
    if (Size < 2) return; // Need at least space for two strings
    size_t name_len = Data[0] % Size;
    size_t string_len = (Size - name_len - 1);

    char *name = (char *)malloc(name_len + 1);
    char *string = (char *)malloc(string_len + 1);

    if (name && string) {
        memcpy(name, Data + 1, name_len);
        name[name_len] = '\0';
        memcpy(string, Data + 1 + name_len, string_len);
        string[string_len] = '\0';

        cJSON *object = cJSON_CreateObject();
        if (object) {
            cJSON *result = cJSON_AddStringToObject(object, name, string);
            if (result == NULL) {
                // Handle error
            }
            cJSON_Delete(object);
        }
    }

    free(name);
    free(string);
}

static void fuzz_cJSON_Print(const uint8_t *Data, size_t Size) {
    char *json_string = (char *)malloc(Size + 1);
    if (!json_string) return;

    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';

    cJSON *item = cJSON_Parse(json_string);
    if (item) {
        char *printed = cJSON_Print(item);
        if (printed) {
            free(printed);
        }
        cJSON_Delete(item);
    }

    free(json_string);
}

static void fuzz_cJSON_PrintUnformatted(const uint8_t *Data, size_t Size) {
    char *json_string = (char *)malloc(Size + 1);
    if (!json_string) return;

    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';

    cJSON *item = cJSON_Parse(json_string);
    if (item) {
        char *printed = cJSON_PrintUnformatted(item);
        if (printed) {
            free(printed);
        }
        cJSON_Delete(item);
    }

    free(json_string);
}

static void fuzz_cJSON_GetErrorPtr(const uint8_t *Data, size_t Size) {
    char *json_string = (char *)malloc(Size + 1);
    if (!json_string) return;

    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';

    cJSON *item = cJSON_Parse(json_string);
    if (!item) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr) {
            // Handle error pointer
        }
    } else {
        cJSON_Delete(item);
    }

    free(json_string);
}

static void fuzz_cJSON_Version(void) {
    const char *version = cJSON_Version();
    // Use version string if needed
}

int LLVMFuzzerTestOneInput_60(const uint8_t *Data, size_t Size) {
    fuzz_cJSON_AddStringToObject(Data, Size);
    fuzz_cJSON_Print(Data, Size);
    fuzz_cJSON_PrintUnformatted(Data, Size);
    fuzz_cJSON_GetErrorPtr(Data, Size);
    fuzz_cJSON_Version();
    return 0;
}