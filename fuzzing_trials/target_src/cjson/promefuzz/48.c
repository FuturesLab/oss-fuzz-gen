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
#include <stdlib.h>
#include <math.h>
#include "cJSON.h"

static double extract_double(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) return 0.0;
    double value;
    memcpy(&value, Data, sizeof(double));
    return value;
}

static int extract_int(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return 0;
    int value;
    memcpy(&value, Data, sizeof(int));
    return value;
}

int LLVMFuzzerTestOneInput_48(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    // Fuzz cJSON_CreateNumber
    double num = extract_double(Data, Size);
    cJSON *number_item = cJSON_CreateNumber(num);
    if (number_item != NULL) {
        cJSON_Delete(number_item);
    }

    // Fuzz cJSON_CreateDoubleArray
    if (Size >= sizeof(double) + sizeof(int)) {
        int count = extract_int(Data, Size);
        if (count > 0 && count <= (Size - sizeof(int)) / sizeof(double)) {
            const double *double_array = (const double *)(Data + sizeof(int));
            cJSON *double_array_item = cJSON_CreateDoubleArray(double_array, count);
            if (double_array_item != NULL) {
                cJSON_Delete(double_array_item);
            }
        }
    }

    // Fuzz cJSON_CreateIntArray
    if (Size >= sizeof(int) * 2) {
        int count = extract_int(Data, Size);
        if (count > 0 && count <= (Size - sizeof(int)) / sizeof(int)) {
            const int *int_array = (const int *)(Data + sizeof(int));
            cJSON *int_array_item = cJSON_CreateIntArray(int_array, count);
            if (int_array_item != NULL) {
                cJSON_Delete(int_array_item);
            }
        }
    }

    // Fuzz cJSON_IsNumber
    cJSON *number_check_item = cJSON_CreateNumber(num);
    if (number_check_item != NULL) {
        cJSON_bool is_number = cJSON_IsNumber(number_check_item);
        (void)is_number; // Suppress unused variable warning
        cJSON_Delete(number_check_item);
    }

    // Fuzz cJSON_GetNumberValue
    cJSON *get_number_item = cJSON_CreateNumber(num);
    if (get_number_item != NULL) {
        double value = cJSON_GetNumberValue(get_number_item);
        (void)value; // Suppress unused variable warning
        cJSON_Delete(get_number_item);
    }

    // Fuzz cJSON_SetNumberHelper
    cJSON *set_number_item = cJSON_CreateNumber(0);
    if (set_number_item != NULL) {
        double set_value = cJSON_SetNumberHelper(set_number_item, num);
        (void)set_value; // Suppress unused variable warning
        cJSON_Delete(set_number_item);
    }

    return 0;
}