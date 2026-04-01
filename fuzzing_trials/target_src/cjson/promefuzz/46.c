// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateDoubleArray at cJSON.c:2686:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateIntArray at cJSON.c:2606:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_IsNumber at cJSON.c:3007:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_GetNumberValue at cJSON.c:109:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_SetNumberHelper at cJSON.c:411:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cJSON.h"

static double get_double_from_data(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return 0.0;
    double num;
    memcpy(&num, Data, sizeof(double));
    return num;
}

static int get_int_from_data(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;
    int num;
    memcpy(&num, Data, sizeof(int));
    return num;
}

static void fuzz_cJSON_CreateNumber(const uint8_t *Data, size_t Size) {
    double num = get_double_from_data(Data, Size);
    cJSON *item = cJSON_CreateNumber(num);
    if (item) {
        cJSON_Delete(item);
    }
}

static void fuzz_cJSON_CreateDoubleArray(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double) || Size % sizeof(double) != 0) return;

    int count = Size / sizeof(double);
    double *numbers = (double *)Data;
    
    cJSON *array = cJSON_CreateDoubleArray(numbers, count);
    if (array) {
        cJSON_Delete(array);
    }
}

static void fuzz_cJSON_CreateIntArray(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int) || Size % sizeof(int) != 0) return;

    int count = Size / sizeof(int);
    int *numbers = (int *)Data;
    
    cJSON *array = cJSON_CreateIntArray(numbers, count);
    if (array) {
        cJSON_Delete(array);
    }
}

static void fuzz_cJSON_IsNumber(const uint8_t *Data, size_t Size) {
    double num = get_double_from_data(Data, Size);
    cJSON *item = cJSON_CreateNumber(num);
    if (item) {
        cJSON_IsNumber(item);
        cJSON_Delete(item);
    }
}

static void fuzz_cJSON_GetNumberValue(const uint8_t *Data, size_t Size) {
    double num = get_double_from_data(Data, Size);
    cJSON *item = cJSON_CreateNumber(num);
    if (item) {
        cJSON_GetNumberValue(item);
        cJSON_Delete(item);
    }
}

static void fuzz_cJSON_SetNumberHelper(const uint8_t *Data, size_t Size) {
    double num = get_double_from_data(Data, Size);
    cJSON *item = cJSON_CreateNumber(0);
    if (item) {
        cJSON_SetNumberHelper(item, num);
        cJSON_Delete(item);
    }
}

int LLVMFuzzerTestOneInput_46(const uint8_t *Data, size_t Size) {
    fuzz_cJSON_CreateNumber(Data, Size);
    fuzz_cJSON_CreateDoubleArray(Data, Size);
    fuzz_cJSON_CreateIntArray(Data, Size);
    fuzz_cJSON_IsNumber(Data, Size);
    fuzz_cJSON_GetNumberValue(Data, Size);
    fuzz_cJSON_SetNumberHelper(Data, Size);
    return 0;
}