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
#include <cstring>
#include <cstdlib>
#include "../cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_22(const uint8_t *Data, size_t Size) {
    // Ensure there's enough data to avoid undefined behavior
    if (Size < 1) return 0;

    // cJSON_Version
    const char* version = cJSON_Version();
    if (version == nullptr) return 0;

    // Prepare a buffer for JSON string
    char* jsonString = (char*)malloc(Size + 1);
    if (jsonString == nullptr) return 0;
    memcpy(jsonString, Data, Size);
    jsonString[Size] = '\0';

    // cJSON_Parse
    cJSON* json = cJSON_Parse(jsonString);
    if (json != nullptr) {
        // cJSON_AddStringToObject
        const char* key = "test_key";
        const char* value = "test_value";
        cJSON* stringItem = cJSON_AddStringToObject(json, key, value);

        // cJSON_PrintUnformatted
        char* unformatted = cJSON_PrintUnformatted(json);
        if (unformatted != nullptr) {
            free(unformatted);
        }

        // cJSON_Print
        char* formatted = cJSON_Print(json);
        if (formatted != nullptr) {
            free(formatted);
        }

        // Cleanup
        cJSON_Delete(json);
    } else {
        // cJSON_GetErrorPtr
        const char* errorPtr = cJSON_GetErrorPtr();
        if (errorPtr != nullptr) {
            // Handle error, if necessary
        }
    }

    free(jsonString);
    return 0;
}