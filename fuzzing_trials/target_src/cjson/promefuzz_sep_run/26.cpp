// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_IsNumber at cJSON.c:3007:26 in cJSON.h
// cJSON_SetNumberHelper at cJSON.c:411:22 in cJSON.h
// cJSON_CreateIntArray at cJSON.c:2606:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_GetNumberValue at cJSON.c:109:22 in cJSON.h
// cJSON_CreateDoubleArray at cJSON.c:2686:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include "cJSON.h"

static void fuzz_cJSON_IsNumber(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cJSON)) return;

    cJSON item;
    memcpy(&item, Data, sizeof(cJSON));
    cJSON_IsNumber(&item);
}

static void fuzz_cJSON_SetNumberHelper(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cJSON) + sizeof(double)) return;

    cJSON object;
    double number;
    memcpy(&object, Data, sizeof(cJSON));
    memcpy(&number, Data + sizeof(cJSON), sizeof(double));

    cJSON_SetNumberHelper(&object, number);
}

static void fuzz_cJSON_CreateIntArray(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;

    int count = Size / sizeof(int);
    cJSON *array = cJSON_CreateIntArray((const int *)Data, count);
    cJSON_Delete(array);
}

static void fuzz_cJSON_GetNumberValue(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(cJSON)) return;

    cJSON item;
    memcpy(&item, Data, sizeof(cJSON));
    cJSON_GetNumberValue(&item);
}

static void fuzz_cJSON_CreateDoubleArray(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;

    int count = Size / sizeof(double);
    cJSON *array = cJSON_CreateDoubleArray((const double *)Data, count);
    cJSON_Delete(array);
}

static void fuzz_cJSON_CreateNumber(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return;

    double num;
    memcpy(&num, Data, sizeof(double));

    cJSON *number = cJSON_CreateNumber(num);
    cJSON_Delete(number);
}

int LLVMFuzzerTestOneInput_26(const uint8_t *Data, size_t Size) {
    fuzz_cJSON_IsNumber(Data, Size);
    fuzz_cJSON_SetNumberHelper(Data, Size);
    fuzz_cJSON_CreateIntArray(Data, Size);
    fuzz_cJSON_GetNumberValue(Data, Size);
    fuzz_cJSON_CreateDoubleArray(Data, Size);
    fuzz_cJSON_CreateNumber(Data, Size);

    return 0;
}