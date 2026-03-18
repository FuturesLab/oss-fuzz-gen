// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateIntArray at cJSON.c:2606:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateIntArray at cJSON.c:2606:23 in cJSON.h
// cJSON_CreateArrayReference at cJSON.c:2556:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateIntArray at cJSON.c:2606:23 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1926:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateFloatArray at cJSON.c:2646:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateStringArray at cJSON.c:2726:23 in cJSON.h
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

#define MAX_ARRAY_SIZE 1024

static void fuzz_cJSON_CreateIntArray(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;
    
    int count = Size / sizeof(int);
    int *numbers = (int *)malloc(count * sizeof(int));
    if (!numbers) return;

    memcpy(numbers, Data, count * sizeof(int));
    cJSON *json = cJSON_CreateIntArray(numbers, count);
    cJSON_Delete(json);
    free(numbers);
}

static void fuzz_cJSON_CreateArrayReference(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;

    int count = Size / sizeof(int);
    int *numbers = (int *)malloc(count * sizeof(int));
    if (!numbers) return;

    memcpy(numbers, Data, count * sizeof(int));
    cJSON *json = cJSON_CreateIntArray(numbers, count);
    if (json) {
        cJSON *ref = cJSON_CreateArrayReference(json);
        cJSON_Delete(ref);
    }
    cJSON_Delete(json);
    free(numbers);
}

static void fuzz_cJSON_GetArrayItem(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;

    int count = Size / sizeof(int);
    int *numbers = (int *)malloc(count * sizeof(int));
    if (!numbers) return;

    memcpy(numbers, Data, count * sizeof(int));
    cJSON *json = cJSON_CreateIntArray(numbers, count);
    if (json) {
        for (int i = 0; i < count; i++) {
            cJSON *item = cJSON_GetArrayItem(json, i);
            (void)item;
        }
    }
    cJSON_Delete(json);
    free(numbers);
}

static void fuzz_cJSON_CreateFloatArray(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float)) return;

    int count = Size / sizeof(float);
    float *numbers = (float *)malloc(count * sizeof(float));
    if (!numbers) return;

    memcpy(numbers, Data, count * sizeof(float));
    cJSON *json = cJSON_CreateFloatArray(numbers, count);
    cJSON_Delete(json);
    free(numbers);
}

static void fuzz_cJSON_CreateArray(const uint8_t *Data, size_t Size) {
    (void)Data; // Unused
    (void)Size; // Unused

    cJSON *json = cJSON_CreateArray();
    cJSON_Delete(json);
}

static void fuzz_cJSON_CreateStringArray(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(char *)) return;

    int count = Size / sizeof(char *);
    char **strings = (char **)malloc(count * sizeof(char *));
    if (!strings) return;

    for (int i = 0; i < count; i++) {
        strings[i] = strndup((const char *)Data + i * sizeof(char *), sizeof(char *));
    }

    cJSON *json = cJSON_CreateStringArray((const char *const *)strings, count);
    cJSON_Delete(json);

    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
}

int LLVMFuzzerTestOneInput_42(const uint8_t *Data, size_t Size) {
    fuzz_cJSON_CreateIntArray(Data, Size);
    fuzz_cJSON_CreateArrayReference(Data, Size);
    fuzz_cJSON_GetArrayItem(Data, Size);
    fuzz_cJSON_CreateFloatArray(Data, Size);
    fuzz_cJSON_CreateArray(Data, Size);
    fuzz_cJSON_CreateStringArray(Data, Size);
    return 0;
}