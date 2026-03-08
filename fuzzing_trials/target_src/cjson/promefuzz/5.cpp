// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddStringToObject at cJSON.c:2195:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddArrayToObject at cJSON.c:2231:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2183:22 in cJSON.h
// cJSON_AddNumberToObject at cJSON.c:2183:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddItemToArray at cJSON.c:2046:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Print at cJSON.c:1302:22 in cJSON.h
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

int LLVMFuzzerTestOneInput_5(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Create a JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) return 0;

    // Add a string to the object
    const char *string_key = "stringKey";
    char *string_value = (char *)malloc(Size + 1);
    if (string_value == NULL) {
        cJSON_Delete(root);
        return 0;
    }
    memcpy(string_value, Data, Size);
    string_value[Size] = '\0';
    cJSON *string_item = cJSON_AddStringToObject(root, string_key, string_value);
    free(string_value);
    if (string_item == NULL) {
        cJSON_Delete(root);
        return 0;
    }

    // Add an array to the object
    const char *array_key = "arrayKey";
    cJSON *array = cJSON_AddArrayToObject(root, array_key);
    if (array == NULL) {
        cJSON_Delete(root);
        return 0;
    }

    // Create another JSON object
    cJSON *inner_object = cJSON_CreateObject();
    if (inner_object == NULL) {
        cJSON_Delete(root);
        return 0;
    }

    // Add numbers to the inner object
    cJSON *number1 = cJSON_AddNumberToObject(inner_object, "number1", (double)(Data[0]));
    cJSON *number2 = cJSON_AddNumberToObject(inner_object, "number2", (double)(Size));
    if (number1 == NULL || number2 == NULL) {
        cJSON_Delete(inner_object);
        cJSON_Delete(root);
        return 0;
    }

    // Add the inner object to the array
    if (!cJSON_AddItemToArray(array, inner_object)) {
        cJSON_Delete(inner_object);
        cJSON_Delete(root);
        return 0;
    }

    // Print the JSON structure
    char *json_string = cJSON_Print(root);
    if (json_string != NULL) {
        free(json_string);
    }

    // Cleanup
    cJSON_Delete(root);
    return 0;
}