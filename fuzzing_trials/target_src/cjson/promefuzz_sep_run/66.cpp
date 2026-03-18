// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_CreateIntArray at cJSON.c:2606:23 in cJSON.h
// cJSON_CreateFloatArray at cJSON.c:2646:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1926:23 in cJSON.h
// cJSON_CreateArrayReference at cJSON.c:2556:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "cJSON.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_66(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    // Create a new JSON array
    cJSON *json_array = cJSON_CreateArray();
    if (!json_array) {
        return 0;
    }

    // Create an integer array from the input data
    int int_count = Size / sizeof(int);
    const int *int_array = (const int *)Data;
    cJSON *int_json_array = cJSON_CreateIntArray(int_array, int_count);

    // Create a float array from the input data
    const float *float_array = (const float *)Data;
    cJSON *float_json_array = cJSON_CreateFloatArray(float_array, int_count);

    // Add items to the JSON array
    cJSON_AddItemToArray(json_array, int_json_array);
    cJSON_AddItemToArray(json_array, float_json_array);

    // Retrieve an item from the array
    int index = int_array[0] % (int_count > 0 ? int_count : 1);
    cJSON *item = cJSON_GetArrayItem(json_array, index);

    // Create an array reference
    cJSON *array_reference = cJSON_CreateArrayReference(json_array);

    // Write data to a dummy file
    write_dummy_file(Data, Size);

    // Clean up
    cJSON_Delete(json_array);
    cJSON_Delete(array_reference);

    return 0;
}