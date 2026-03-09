#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
extern "C" {
#include "../cJSON.h"
}

#include <cstddef>
#include <cstdint>
#include <cstring>

static char* createNullTerminatedString(const uint8_t* data, size_t size) {
    char* str = static_cast<char*>(malloc(size + 1));
    if (str == nullptr) {
        return nullptr;
    }
    memcpy(str, data, size);
    str[size] = '\0';
    return str;
}

extern "C" int LLVMFuzzerTestOneInput_13(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    // Create a null-terminated string from the input data
    char* inputString = createNullTerminatedString(Data, Size);
    if (inputString == nullptr) {
        return 0;
    }

    // Initialize cJSON hooks with default (NULL)
    cJSON_Hooks hooks;
    hooks.malloc_fn = nullptr;
    hooks.free_fn = nullptr;
    cJSON_InitHooks(&hooks);

    // Create cJSON string
    cJSON* jsonString1 = cJSON_CreateString(inputString);
    cJSON* jsonString2 = cJSON_CreateString(inputString);
    cJSON* jsonString3 = cJSON_CreateString(inputString);

    // Create cJSON array
    cJSON* jsonArray = cJSON_CreateArray();

    // Add items to array
    if (jsonArray != nullptr && jsonString1 != nullptr) {
        cJSON_AddItemToArray(jsonArray, jsonString1);
    }

    if (jsonArray != nullptr && jsonString2 != nullptr) {
        cJSON_AddItemToArray(jsonArray, jsonString2);
    }

    // Create a cJSON object
    cJSON* jsonObject = cJSON_CreateObject();

    // Add item to object
    if (jsonObject != nullptr && jsonString3 != nullptr) {
        cJSON_AddItemToObject(jsonObject, "key", jsonString3);
    }

    // Get array size
    if (jsonArray != nullptr) {
        int arraySize = cJSON_GetArraySize(jsonArray);
    }

    // Clean up
    cJSON_Delete(jsonArray);
    cJSON_Delete(jsonObject);

    free(inputString);

    return 0;
}