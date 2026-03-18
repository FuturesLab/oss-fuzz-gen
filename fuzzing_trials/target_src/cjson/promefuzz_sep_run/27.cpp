// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateTrue at cJSON.c:2457:23 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
// cJSON_IsBool at cJSON.c:2988:26 in cJSON.h
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddBoolToObject at cJSON.c:2171:22 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_IsFalse at cJSON.c:2967:26 in cJSON.h
// cJSON_CreateBool at cJSON.c:2479:23 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
// cJSON_IsFalse at cJSON.c:2967:26 in cJSON.h
// cJSON_IsBool at cJSON.c:2988:26 in cJSON.h
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
#include "cJSON.h"

int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    // Create a cJSON item representing true
    cJSON *true_item = cJSON_CreateTrue();
    if (true_item == NULL) {
        return 0; // Memory allocation failed, exit
    }

    // Check if the item is true
    cJSON_bool is_true = cJSON_IsTrue(true_item);
    (void)is_true; // Suppress unused variable warning

    // Check if the item is boolean
    cJSON_bool is_bool = cJSON_IsBool(true_item);
    (void)is_bool; // Suppress unused variable warning

    // Create a JSON object
    cJSON *json_object = cJSON_CreateObject();
    if (json_object == NULL) {
        cJSON_Delete(true_item);
        return 0; // Memory allocation failed, exit
    }

    // Add a boolean to the JSON object
    if (Size > 0) {
        // Use the first byte of data as a boolean value
        cJSON_bool bool_value = Data[0] % 2;
        cJSON *added_item = cJSON_AddBoolToObject(json_object, "test_bool", bool_value);
        if (added_item == NULL) {
            cJSON_Delete(true_item);
            cJSON_Delete(json_object);
            return 0; // Failed to add boolean to object
        }
    }

    // Check if the item is false
    cJSON_bool is_false = cJSON_IsFalse(true_item);
    (void)is_false; // Suppress unused variable warning

    // Create a boolean item based on the input
    if (Size > 0) {
        cJSON_bool bool_value = Data[0] % 2;
        cJSON *bool_item = cJSON_CreateBool(bool_value);
        if (bool_item != NULL) {
            cJSON_bool check_true = cJSON_IsTrue(bool_item);
            cJSON_bool check_false = cJSON_IsFalse(bool_item);
            cJSON_bool check_bool = cJSON_IsBool(bool_item);
            (void)check_true;  // Suppress unused variable warning
            (void)check_false; // Suppress unused variable warning
            (void)check_bool;  // Suppress unused variable warning
            cJSON_Delete(bool_item);
        }
    }

    // Cleanup
    cJSON_Delete(true_item);
    cJSON_Delete(json_object);

    return 0;
}