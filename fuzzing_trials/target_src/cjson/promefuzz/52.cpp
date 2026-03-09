// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_Print at cJSON.c:1302:22 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_GetErrorPtr at cJSON.c:94:28 in cJSON.h
// cJSON_Version at cJSON.c:124:27 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
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

static void fuzz_cJSON_AddStringToObject(cJSON *object, const uint8_t *Data, size_t Size) {
    if (Size < 3) return;  // Ensure there's enough data for name length and at least one char for name and string
    size_t name_len = Data[0] % (Size - 2);  // Length of the name string
    const char *name = (const char *)(Data + 1);
    if (name_len + 2 >= Size) return;  // Check if there's enough data for both name and string
    const char *string = (const char *)(Data + 1 + name_len);
    
    // Ensure null-termination
    char *name_buf = (char *)malloc(name_len + 1);
    if (!name_buf) return;
    memcpy(name_buf, name, name_len);
    name_buf[name_len] = '\0';

    size_t string_len = Size - 1 - name_len;
    char *string_buf = (char *)malloc(string_len + 1);
    if (!string_buf) {
        free(name_buf);
        return;
    }
    memcpy(string_buf, string, string_len);
    string_buf[string_len] = '\0';

    cJSON *result = cJSON_AddStringToObject(object, name_buf, string_buf);
    // No need to delete 'result' since it's part of 'object' now

    free(name_buf);
    free(string_buf);
}

static void fuzz_cJSON_Print(cJSON *item) {
    char *printed = cJSON_Print(item);
    if (printed != NULL) {
        free(printed);
    }
}

static void fuzz_cJSON_PrintUnformatted(cJSON *item) {
    char *printed = cJSON_PrintUnformatted(item);
    if (printed != NULL) {
        free(printed);
    }
}

static void fuzz_cJSON_Parse(const uint8_t *Data, size_t Size) {
    char *json_data = (char *)malloc(Size + 1);
    if (!json_data) return;
    memcpy(json_data, Data, Size);
    json_data[Size] = '\0';  // Ensure null-termination

    cJSON *parsed = cJSON_Parse(json_data);
    if (parsed != NULL) {
        fuzz_cJSON_Print(parsed);
        fuzz_cJSON_PrintUnformatted(parsed);
        cJSON_Delete(parsed);
    }

    const char *error_ptr = cJSON_GetErrorPtr();
    (void)error_ptr;  // Avoid unused variable warning

    free(json_data);
}

int LLVMFuzzerTestOneInput_52(const uint8_t *Data, size_t Size) {
    // Fuzz cJSON_Version
    const char *version = cJSON_Version();
    (void)version;  // Avoid unused variable warning

    // Fuzz cJSON_Parse
    fuzz_cJSON_Parse(Data, Size);

    // Create a new JSON object to fuzz cJSON_AddStringToObject
    cJSON *object = cJSON_CreateObject();
    if (object != NULL) {
        fuzz_cJSON_AddStringToObject(object, Data, Size);
        cJSON_Delete(object);
    }

    return 0;
}