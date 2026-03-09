// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_Version at cJSON.c:124:27 in cJSON.h
// cJSON_Print at cJSON.c:1302:22 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_GetErrorPtr at cJSON.c:94:28 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
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

static void fuzz_cJSON_AddStringToObject(cJSON *object, const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    size_t key_len = Data[0] % (Size - 1);
    size_t value_len = Size - 1 - key_len;

    char *key = (char *)malloc(key_len + 1);
    char *value = (char *)malloc(value_len + 1);

    if (key == NULL || value == NULL) {
        free(key);
        free(value);
        return;
    }

    memcpy(key, Data + 1, key_len);
    key[key_len] = '\0';

    memcpy(value, Data + 1 + key_len, value_len);
    value[value_len] = '\0';

    cJSON_AddStringToObject(object, key, value);

    free(key);
    free(value);
}

static void fuzz_cJSON_Version() {
    const char *version = cJSON_Version();
    (void)version; // Suppress unused variable warning
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

static void fuzz_cJSON_GetErrorPtr() {
    const char *error = cJSON_GetErrorPtr();
    (void)error; // Suppress unused variable warning
}

static void fuzz_cJSON_Parse(const uint8_t *Data, size_t Size) {
    char *json_string = (char *)malloc(Size + 1);
    if (json_string == NULL) {
        return;
    }

    memcpy(json_string, Data, Size);
    json_string[Size] = '\0';

    cJSON *parsed = cJSON_Parse(json_string);
    if (parsed != NULL) {
        fuzz_cJSON_Print(parsed);
        fuzz_cJSON_PrintUnformatted(parsed);
        cJSON_Delete(parsed);
    } else {
        fuzz_cJSON_GetErrorPtr();
    }

    free(json_string);
}

int LLVMFuzzerTestOneInput_55(const uint8_t *Data, size_t Size) {
    cJSON *object = cJSON_CreateObject();
    if (object == NULL) {
        return 0;
    }

    fuzz_cJSON_AddStringToObject(object, Data, Size);
    fuzz_cJSON_Version();
    fuzz_cJSON_Parse(Data, Size);

    cJSON_Delete(object);
    return 0;
}