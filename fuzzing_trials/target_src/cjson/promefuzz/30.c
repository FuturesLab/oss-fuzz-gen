// This fuzz driver is generated for library cjson, aiming to fuzz the following functions:
// cJSON_CreateObject at cJSON.c:2594:23 in cJSON.h
// cJSON_CreateBool at cJSON.c:2479:23 in cJSON.h
// cJSON_AddItemToObject at cJSON.c:2104:26 in cJSON.h
// cJSON_IsBool at cJSON.c:2988:26 in cJSON.h
// cJSON_IsTrue at cJSON.c:2977:26 in cJSON.h
// cJSON_IsFalse at cJSON.c:2967:26 in cJSON.h
// cJSON_CreateTrue at cJSON.c:2457:23 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
// cJSON_AddBoolToObject at cJSON.c:2171:22 in cJSON.h
// cJSON_IsBool at cJSON.c:2988:26 in cJSON.h
// cJSON_Delete at cJSON.c:253:20 in cJSON.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "cJSON.h"

int LLVMFuzzerTestOneInput_30(const uint8_t *Data, size_t Size) {
    // Check if Size is sufficient to form a valid string
    if (Size < 1) {
        return 0;
    }
    
    // Create a cJSON object
    cJSON *json_object = cJSON_CreateObject();
    if (!json_object) {
        return 0; // Memory allocation failed
    }

    // Create a boolean item using cJSON_CreateBool
    cJSON_bool bool_value = Data[0] % 2; // Use the first byte to decide true or false
    cJSON *bool_item = cJSON_CreateBool(bool_value);

    // Add the boolean item to the JSON object
    if (bool_item) {
        cJSON_AddItemToObject(json_object, "bool_key", bool_item);
    }

    // Test cJSON_IsBool
    cJSON_IsBool(bool_item);

    // Test cJSON_IsTrue and cJSON_IsFalse
    cJSON_IsTrue(bool_item);
    cJSON_IsFalse(bool_item);

    // Test cJSON_CreateTrue
    cJSON *true_item = cJSON_CreateTrue();
    if (true_item) {
        cJSON_Delete(true_item);
    }

    // Test cJSON_AddBoolToObject
    cJSON *added_item = cJSON_AddBoolToObject(json_object, "added_bool", bool_value);
    if (added_item) {
        // Test cJSON_IsBool on the newly added item
        cJSON_IsBool(added_item);
    }

    // Clean up
    cJSON_Delete(json_object);

    return 0;
}