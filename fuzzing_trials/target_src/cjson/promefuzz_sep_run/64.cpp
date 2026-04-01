// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_CreateIntArray at cJSON.c:2606:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_CreateFloatArray at cJSON.c:2646:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1926:23 in cJSON.h
// cJSON_CreateArrayReference at cJSON.c:2556:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cJSON.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file != NULL) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_64(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    // Write data to dummy file
    write_dummy_file(Data, Size);

    // Create an array using cJSON_CreateArray
    cJSON *array = cJSON_CreateArray();
    if (array == NULL) {
        return 0; // Memory allocation failed
    }

    // Create an integer array from the input data
    int *int_array = (int *)Data;
    size_t int_count = Size / sizeof(int);
    cJSON *int_json_array = cJSON_CreateIntArray(int_array, int_count);
    if (int_json_array != NULL) {
        cJSON_AddItemToArray(array, int_json_array);
    }

    // Create a float array from the input data
    float *float_array = (float *)Data;
    size_t float_count = Size / sizeof(float);
    cJSON *float_json_array = cJSON_CreateFloatArray(float_array, float_count);
    if (float_json_array != NULL) {
        cJSON_AddItemToArray(array, float_json_array);
    }

    // Get an array item
    if (int_count > 0) {
        int index = int_array[0] % int_count; // Use the first int as an index
        cJSON *item = cJSON_GetArrayItem(array, index);
        if (item != NULL) {
            // Do something with the item
        }
    }

    // Create a reference to the array
    cJSON *array_ref = cJSON_CreateArrayReference(array);
    if (array_ref != NULL) {
        // Do something with the reference
    }

    // Cleanup
    cJSON_Delete(array);

    return 0;
}