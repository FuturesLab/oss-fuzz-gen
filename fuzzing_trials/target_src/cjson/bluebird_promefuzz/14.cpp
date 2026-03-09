#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "../cJSON.h"
#include <cstdint>
#include <cstddef>
#include <cstring>

extern "C" int LLVMFuzzerTestOneInput_14(const uint8_t *Data, size_t Size) {
    // Prepare the environment
    cJSON *jsonObject = cJSON_CreateObject();
    if (jsonObject == nullptr) {
        return 0; // If creation fails, exit early
    }

    // Ensure the data is null-terminated for use as a string
    char *key = nullptr;
    if (Size > 0) {
        key = new char[Size + 1];
        std::memcpy(key, Data, Size);
        key[Size] = '\0'; // Null-terminate the string
    }

    // Invoke the target function
    cJSON *result = cJSON_AddTrueToObject(jsonObject, key);
    
    // Clean up
    cJSON_Delete(jsonObject);
    delete[] key;

    return 0;
}