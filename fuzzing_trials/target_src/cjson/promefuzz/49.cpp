// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_GetStringValue at cJSON.c:99:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateRaw at cJSON.c:2566:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2533:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
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

static void fuzz_cJSON_AddStringToObject(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    
    cJSON *object = cJSON_CreateObject();
    if (object == NULL) return;

    char *key = strndup((const char *)Data, Size / 2);
    char *value = strndup((const char *)(Data + Size / 2), Size - Size / 2);

    if (key != NULL && value != NULL) {
        cJSON *result = cJSON_AddStringToObject(object, key, value);
        (void)result; // Suppress unused variable warning
    }
    
    free(key);
    free(value);
    cJSON_Delete(object);
}

static void fuzz_cJSON_GetStringValue(const uint8_t *Data, size_t Size) {
    if (Size == 0) return;

    char *input = strndup((const char *)Data, Size);
    if (input == NULL) return;

    cJSON *item = cJSON_CreateString(input);
    if (item != NULL) {
        char *value = cJSON_GetStringValue(item);
        (void)value; // Suppress unused variable warning
        cJSON_Delete(item);
    }

    free(input);
}

static void fuzz_cJSON_CreateRaw(const uint8_t *Data, size_t Size) {
    char *input = strndup((const char *)Data, Size);
    if (input == NULL) return;

    cJSON *raw = cJSON_CreateRaw(input);

    free(input);
    cJSON_Delete(raw);
}

static void fuzz_cJSON_PrintUnformatted(const uint8_t *Data, size_t Size) {
    char *input = strndup((const char *)Data, Size);
    if (input == NULL) return;

    cJSON *item = cJSON_Parse(input);
    if (item != NULL) {
        char *output = cJSON_PrintUnformatted(item);
        if (output != NULL) {
            free(output);
        }
        cJSON_Delete(item);
    }

    free(input);
}

static void fuzz_cJSON_CreateStringReference(const uint8_t *Data, size_t Size) {
    char *input = strndup((const char *)Data, Size);
    if (input == NULL) return;

    cJSON *stringRef = cJSON_CreateStringReference(input);

    cJSON_Delete(stringRef);
    free(input);
}

static void fuzz_cJSON_Parse(const uint8_t *Data, size_t Size) {
    char *input = strndup((const char *)Data, Size);
    if (input == NULL) return;

    cJSON *parsed = cJSON_Parse(input);

    cJSON_Delete(parsed);
    free(input);
}

int LLVMFuzzerTestOneInput_49(const uint8_t *Data, size_t Size) {
    fuzz_cJSON_AddStringToObject(Data, Size);
    fuzz_cJSON_GetStringValue(Data, Size);
    fuzz_cJSON_CreateRaw(Data, Size);
    fuzz_cJSON_PrintUnformatted(Data, Size);
    fuzz_cJSON_CreateStringReference(Data, Size);
    fuzz_cJSON_Parse(Data, Size);
    
    return 0;
}