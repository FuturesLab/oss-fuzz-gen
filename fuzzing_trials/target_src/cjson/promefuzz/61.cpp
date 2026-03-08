// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_Print at cJSON.c:1302:22 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_GetErrorPtr at cJSON.c:94:28 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Version at cJSON.c:124:27 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

static void fuzz_cJSON_AddStringToObject(cJSON *object, const uint8_t *Data, size_t Size) {
    if (Size < 2) return; // Ensure there's enough data for at least two strings
    size_t name_len = Data[0] % (Size - 1);
    size_t string_len = Size - 1 - name_len;
    
    char *name = (char *)malloc(name_len + 1);
    char *string = (char *)malloc(string_len + 1);
    if (!name || !string) {
        free(name);
        free(string);
        return;
    }
    
    memcpy(name, Data + 1, name_len);
    memcpy(string, Data + 1 + name_len, string_len);
    name[name_len] = '\0';
    string[string_len] = '\0';
    
    cJSON *result = cJSON_AddStringToObject(object, name, string);
    if (result == NULL) {
        // Handle error if necessary
    }
    
    free(name);
    free(string);
}

static void fuzz_cJSON_PrintFunctions(cJSON *item) {
    char *printed = cJSON_Print(item);
    if (printed) {
        free(printed);
    }

    char *unformatted = cJSON_PrintUnformatted(item);
    if (unformatted) {
        free(unformatted);
    }
}

static void fuzz_cJSON_Parse(const uint8_t *Data, size_t Size) {
    char *json_string = (char *)malloc(Size + 1);
    if (!json_string) return;

    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';

    cJSON *parsed = cJSON_Parse(json_string);
    if (parsed) {
        fuzz_cJSON_PrintFunctions(parsed);
        cJSON_Delete(parsed);
    } else {
        const char *error_ptr = cJSON_GetErrorPtr();
        // Handle the error if needed
    }

    free(json_string);
}

int LLVMFuzzerTestOneInput_61(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    cJSON *root = cJSON_CreateObject();
    if (!root) return 0;

    fuzz_cJSON_AddStringToObject(root, Data, Size);
    fuzz_cJSON_Parse(Data, Size);

    cJSON_Delete(root);

    // Retrieve and print the cJSON version
    const char *version = cJSON_Version();
    (void)version; // Suppress unused variable warning

    return 0;
}