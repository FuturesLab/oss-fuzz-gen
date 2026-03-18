// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_CreateIntArray at cJSON.c:2606:23 in cJSON.h
// cJSON_CreateFloatArray at cJSON.c:2646:23 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1926:23 in cJSON.h
// cJSON_GetArrayItem at cJSON.c:1926:23 in cJSON.h
// cJSON_CreateArrayReference at cJSON.c:2556:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_65(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(int)) {
        return 0;
    }

    // Prepare integer array from input data
    int *intArray = (int *)Data;
    int intCount = Size / sizeof(int);

    // Prepare float array from input data
    float *floatArray = (float *)Data;
    int floatCount = Size / sizeof(float);

    // Create arrays
    cJSON *jsonArray = cJSON_CreateArray();
    cJSON *intJsonArray = cJSON_CreateIntArray(intArray, intCount);
    cJSON *floatJsonArray = cJSON_CreateFloatArray(floatArray, floatCount);

    // Add items to the jsonArray
    if (jsonArray && intJsonArray) {
        cJSON_AddItemToArray(jsonArray, intJsonArray);
    }
    if (jsonArray && floatJsonArray) {
        cJSON_AddItemToArray(jsonArray, floatJsonArray);
    }

    // Get array item at index 0 and 1
    cJSON *item0 = cJSON_GetArrayItem(jsonArray, 0);
    cJSON *item1 = cJSON_GetArrayItem(jsonArray, 1);

    // Create array reference
    cJSON *arrayReference = cJSON_CreateArrayReference(jsonArray);

    // Cleanup
    cJSON_Delete(jsonArray);
    cJSON_Delete(arrayReference);

    // Write data to a dummy file
    write_dummy_file(Data, Size);

    return 0;
}