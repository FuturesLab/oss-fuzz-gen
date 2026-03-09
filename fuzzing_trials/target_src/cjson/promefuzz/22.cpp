// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddObjectToObject at cJSON.c:2219:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddTrueToObject at cJSON.c:2147:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddArrayToObject at cJSON.c:2231:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
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
#include <stdlib.h>
#include "cJSON.h"

static void initialize_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Initialize a dummy file with input data
    initialize_dummy_file(Data, Size);

    // Ensure the input data is null-terminated
    char *null_terminated_data = (char *)malloc(Size + 1);
    if (null_terminated_data == NULL) {
        return 0;
    }
    memcpy(null_terminated_data, Data, Size);
    null_terminated_data[Size] = '\0';

    // Create a root JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) {
        free(null_terminated_data);
        return 0;
    }

    // Attempt to add a string to the JSON object
    cJSON *stringItem = cJSON_AddStringToObject(root, "key1", null_terminated_data);
    if (stringItem == NULL) {
        cJSON_Delete(root);
        free(null_terminated_data);
        return 0;
    }

    // Attempt to add an object to the JSON object
    cJSON *childObject = cJSON_AddObjectToObject(root, "objectKey");
    if (childObject == NULL) {
        cJSON_Delete(root);
        free(null_terminated_data);
        return 0;
    }

    // Attempt to add a true value to the JSON object
    cJSON *trueItem = cJSON_AddTrueToObject(root, "trueKey");
    if (trueItem == NULL) {
        cJSON_Delete(root);
        free(null_terminated_data);
        return 0;
    }

    // Attempt to add an array to the JSON object
    cJSON *array = cJSON_AddArrayToObject(root, "arrayKey");
    if (array == NULL) {
        cJSON_Delete(root);
        free(null_terminated_data);
        return 0;
    }

    // Create a new item to add to the array
    cJSON *arrayItem = cJSON_CreateString(null_terminated_data);
    if (arrayItem == NULL) {
        cJSON_Delete(root);
        free(null_terminated_data);
        return 0;
    }

    // Attempt to add the item to the array
    cJSON_bool addItemResult = cJSON_AddItemToArray(array, arrayItem);
    if (!addItemResult) {
        cJSON_Delete(root);
        cJSON_Delete(arrayItem);
        free(null_terminated_data);
        return 0;
    }

    // Clean up
    cJSON_Delete(root);
    free(null_terminated_data);

    return 0;
}