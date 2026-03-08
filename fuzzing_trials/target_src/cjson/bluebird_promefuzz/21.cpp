#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstddef>
#include <cstdint>
#include "../cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_21(const uint8_t *Data, size_t Size) {
    // Ensure that the input data is sufficient to extract required names and boolean values
    if (Size < 3) return 0;

    // Create a new cJSON object
    cJSON *jsonObject = cJSON_CreateObject();
    if (jsonObject == nullptr) return 0; // Memory allocation failed

    // Ensure null-terminated strings for names
    std::string name1(reinterpret_cast<const char*>(Data), Size - 2);
    std::string name2(reinterpret_cast<const char*>(Data + 1), Size - 2);

    cJSON_bool boolValue1 = static_cast<cJSON_bool>(Data[Size - 1] % 2); // Use the last byte for boolean value
    cJSON_bool boolValue2 = static_cast<cJSON_bool>(Data[Size - 2] % 2); // Use the second last byte for boolean value

    // Add boolean values to the JSON object
    cJSON *item1 = cJSON_AddBoolToObject(jsonObject, name1.c_str(), boolValue1);
    if (item1 == nullptr) {
        cJSON_Delete(jsonObject);
        return 0; // Failed to add the first boolean item
    }

    cJSON *item2 = cJSON_AddBoolToObject(jsonObject, name2.c_str(), boolValue2);
    if (item2 == nullptr) {
        cJSON_Delete(jsonObject);
        return 0; // Failed to add the second boolean item
    }

    // Clean up and delete the JSON object
    cJSON_Delete(jsonObject);
    return 0;
}