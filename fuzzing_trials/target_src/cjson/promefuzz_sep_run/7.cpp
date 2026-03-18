// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_Print at cJSON.c:1302:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateString at cJSON.c:2516:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateArray at cJSON.c:2583:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateNumber at cJSON.c:2490:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
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

int LLVMFuzzerTestOneInput_7(const uint8_t *Data, size_t Size) {
    if (Size < 3) return 0; // Ensure there is enough data for meaningful operations

    // Create a JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) return 0;

    // Create a JSON string from input data
    char *key = (char *)malloc(Size + 1);
    if (key == NULL) {
        cJSON_Delete(root);
        return 0;
    }
    memcpy(key, Data, Size);
    key[Size] = '\0';

    cJSON *string_item = cJSON_CreateString(key);
    free(key);
    if (string_item == NULL) {
        cJSON_Delete(root);
        return 0;
    }

    // Add the string to the object
    if (!cJSON_AddItemToObject(root, "key", string_item)) {
        cJSON_Delete(string_item);
        cJSON_Delete(root);
        return 0;
    }

    // Create a JSON array
    cJSON *array = cJSON_CreateArray();
    if (array == NULL) {
        cJSON_Delete(root);
        return 0;
    }

    // Add the array to the object
    if (!cJSON_AddItemToObject(root, "array", array)) {
        cJSON_Delete(array);
        cJSON_Delete(root);
        return 0;
    }

    // Create another JSON object
    cJSON *inner_object = cJSON_CreateObject();
    if (inner_object == NULL) {
        cJSON_Delete(root);
        return 0;
    }

    // Add the object to the array
    if (!cJSON_AddItemToArray(array, inner_object)) {
        cJSON_Delete(inner_object);
        cJSON_Delete(root);
        return 0;
    }

    // Create a number from a part of the input data
    double num1 = (double)Data[0];
    cJSON *number_item1 = cJSON_CreateNumber(num1);
    if (number_item1 == NULL) {
        cJSON_Delete(root);
        return 0;
    }

    // Add the number to the object
    if (!cJSON_AddItemToObject(inner_object, "num1", number_item1)) {
        cJSON_Delete(number_item1);
        cJSON_Delete(root);
        return 0;
    }

    // Create another number from a part of the input data
    double num2 = (double)Data[1];
    cJSON *number_item2 = cJSON_CreateNumber(num2);
    if (number_item2 == NULL) {
        cJSON_Delete(root);
        return 0;
    }

    // Add the number to the object
    if (!cJSON_AddItemToObject(inner_object, "num2", number_item2)) {
        cJSON_Delete(number_item2);
        cJSON_Delete(root);
        return 0;
    }

    // Print the JSON object
    char *json_string = cJSON_Print(root);
    if (json_string != NULL) {
        // Normally, you would use the string here
        free(json_string);
    }

    // Clean up
    cJSON_Delete(root);
    return 0;
}