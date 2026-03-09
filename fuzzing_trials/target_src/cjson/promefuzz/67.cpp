// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_CreateIntArray at cJSON.c:2606:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1926:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_CreateArrayReference at cJSON.c:2556:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateIntArray at cJSON.c:2606:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateFloatArray at cJSON.c:2646:23 in cJSON.h
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

static void fuzz_cJSON_GetArrayItem(const uint8_t *Data, size_t Size) {
    cJSON *array = cJSON_CreateArray();
    if (array == NULL) {
        return;
    }

    // Create a small int array and add it to the cJSON array
    int int_data[] = {1, 2, 3, 4, 5};
    cJSON *int_array = cJSON_CreateIntArray(int_data, 5);
    if (int_array != NULL) {
        cJSON_AddItemToArray(array, int_array);
    }

    // Use the fuzz data as an index
    if (Size >= sizeof(int)) {
        int index;
        memcpy(&index, Data, sizeof(int));
        cJSON *item = cJSON_GetArrayItem(array, index);
        if (item != NULL) {
            // Do something with item if needed
        }
    }

    cJSON_Delete(array);
}

static void fuzz_cJSON_CreateArrayReference(const uint8_t *Data, size_t Size) {
    cJSON *array = cJSON_CreateArray();
    if (array == NULL) {
        return;
    }

    cJSON *ref = cJSON_CreateArrayReference(array);
    if (ref != NULL) {
        cJSON_Delete(ref);
    }

    cJSON_Delete(array);
}

static void fuzz_cJSON_CreateIntArray(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) return;

    int count = Size / sizeof(int);
    int *numbers = (int *)Data;
    cJSON *int_array = cJSON_CreateIntArray(numbers, count);
    if (int_array != NULL) {
        cJSON_Delete(int_array);
    }
}

static void fuzz_cJSON_CreateFloatArray(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(float)) return;

    int count = Size / sizeof(float);
    float *numbers = (float *)Data;
    cJSON *float_array = cJSON_CreateFloatArray(numbers, count);
    if (float_array != NULL) {
        cJSON_Delete(float_array);
    }
}

int LLVMFuzzerTestOneInput_67(const uint8_t *Data, size_t Size) {
    fuzz_cJSON_GetArrayItem(Data, Size);
    fuzz_cJSON_CreateArrayReference(Data, Size);
    fuzz_cJSON_CreateIntArray(Data, Size);
    fuzz_cJSON_CreateFloatArray(Data, Size);

    return 0;
}