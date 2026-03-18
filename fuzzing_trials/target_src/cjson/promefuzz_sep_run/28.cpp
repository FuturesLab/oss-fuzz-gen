// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_ReplaceItemInObject at cJSON.c:2435:26 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_PrintUnformatted at cJSON.c:1307:22 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_malloc at cJSON.c:3182:22 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "cJSON.h"

static void fuzz_cJSON_AddStringToObject(cJSON *object, const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    char *key = strndup((const char *)Data, Size / 2);
    char *value = strndup((const char *)Data + Size / 2, Size - Size / 2);
    cJSON_AddStringToObject(object, key, value);
    free(key);
    free(value);
}

static void fuzz_cJSON_ReplaceItemInObject(cJSON *object, const uint8_t *Data, size_t Size) {
    if (Size < 2) return;
    char *key = strndup((const char *)Data, Size / 2);
    cJSON *newitem = cJSON_CreateNumber((double)Data[Size / 2]);
    cJSON_ReplaceItemInObject(object, key, newitem);
    // Do not delete newitem here as it is managed by the cJSON object now
    free(key);
}

static void fuzz_cJSON_AddItemToArray(cJSON *array, const uint8_t *Data, size_t Size) {
    cJSON *item = cJSON_CreateNumber((double)(Size > 0 ? Data[0] : 0));
    cJSON_AddItemToArray(array, item);
}

static void fuzz_cJSON_PrintUnformatted(cJSON *item) {
    char *out = cJSON_PrintUnformatted(item);
    if (out) {
        free(out);
    }
}

static void fuzz_cJSON_CreateNumber(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;
    double num;
    memcpy(&num, Data, sizeof(double));
    cJSON *item = cJSON_CreateNumber(num);
    if (item) {
        cJSON_Delete(item);
    }
}

static void fuzz_cJSON_malloc(const uint8_t *Data, size_t Size) {
    void *ptr = cJSON_malloc(Size);
    if (ptr) {
        memset(ptr, 0, Size);
        free(ptr);
    }
}

int LLVMFuzzerTestOneInput_28(const uint8_t *Data, size_t Size) {
    cJSON *json = cJSON_CreateObject();
    if (!json) return 0;

    fuzz_cJSON_AddStringToObject(json, Data, Size);
    fuzz_cJSON_ReplaceItemInObject(json, Data, Size);

    cJSON *array = cJSON_CreateArray();
    if (array) {
        fuzz_cJSON_AddItemToArray(array, Data, Size);
        cJSON_Delete(array);
    }

    fuzz_cJSON_PrintUnformatted(json);
    fuzz_cJSON_CreateNumber(Data, Size);
    fuzz_cJSON_malloc(Data, Size);

    cJSON_Delete(json);
    return 0;
}