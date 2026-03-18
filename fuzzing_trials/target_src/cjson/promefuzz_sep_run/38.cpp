// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_GetStringValue at cJSON.c:99:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateRaw at cJSON.c:2566:23 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateStringReference at cJSON.c:2533:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Parse at cJSON.c:1222:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddArrayToObject at cJSON.c:2231:22 in cJSON.h
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

static void fuzz_cJSON_GetStringValue(const uint8_t *Data, size_t Size) {
    if (Size == 0 || Data[Size - 1] != '\0') return; // Ensure null-terminated string
    cJSON *item = cJSON_Parse((const char *)Data);
    if (item) {
        char *str = cJSON_GetStringValue(item);
        if (str) {
            // Do something with the string
        }
        cJSON_Delete(item);
    }
}

static void fuzz_cJSON_CreateRaw(const uint8_t *Data, size_t Size) {
    if (Size == 0 || Data[Size - 1] != '\0') return; // Ensure null-terminated string
    cJSON *rawItem = cJSON_CreateRaw((const char *)Data);
    if (rawItem) {
        char *unformatted = cJSON_PrintUnformatted(rawItem);
        if (unformatted) {
            free(unformatted);
        }
        cJSON_Delete(rawItem);
    }
}

static void fuzz_cJSON_CreateStringReference(const uint8_t *Data, size_t Size) {
    if (Size == 0 || Data[Size - 1] != '\0') return; // Ensure null-terminated string
    cJSON *stringRef = cJSON_CreateStringReference((const char *)Data);
    if (stringRef) {
        cJSON_Delete(stringRef);
    }
}

static void fuzz_cJSON_Parse(const uint8_t *Data, size_t Size) {
    if (Size == 0 || Data[Size - 1] != '\0') return; // Ensure null-terminated string
    cJSON *parsed = cJSON_Parse((const char *)Data);
    if (parsed) {
        cJSON_Delete(parsed);
    }
}

static void fuzz_cJSON_AddArrayToObject(const uint8_t *Data, size_t Size) {
    if (Size < 2) return;

    cJSON *object = cJSON_CreateObject();
    if (!object) return;

    char *name = (char *)malloc(Size);
    if (!name) {
        cJSON_Delete(object);
        return;
    }
    memcpy(name, Data, Size - 1);
    name[Size - 1] = '\0';

    cJSON *array = cJSON_AddArrayToObject(object, name);
    if (array) {
        // Do something with the array
    }

    free(name);
    cJSON_Delete(object);
}

int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    fuzz_cJSON_GetStringValue(Data, Size);
    fuzz_cJSON_CreateRaw(Data, Size);
    fuzz_cJSON_CreateStringReference(Data, Size);
    fuzz_cJSON_Parse(Data, Size);
    fuzz_cJSON_AddArrayToObject(Data, Size);
    return 0;
}