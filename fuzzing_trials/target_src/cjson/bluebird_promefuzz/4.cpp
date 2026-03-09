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
#include <cstring>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Create a cJSON object from the input data
    cJSON *json = cJSON_ParseWithLength(reinterpret_cast<const char *>(Data), Size);
    if (!json) {
        return 0;
    }

    // Prepare a buffer for cJSON_PrintPreallocated
    size_t buffer_size = Size + 5; // Allocate additional 5 bytes as recommended
    char *buffer = static_cast<char *>(malloc(buffer_size));
    if (!buffer) {
        cJSON_Delete(json);
        return 0;
    }

    // Test cJSON_PrintPreallocated
    cJSON_PrintPreallocated(json, buffer, buffer_size, cJSON_False);
    cJSON_PrintPreallocated(json, buffer, buffer_size, cJSON_True);

    // Test cJSON_AddNullToObject
    cJSON_AddNullToObject(json, "test_null");

    // Test cJSON_IsObject
    cJSON_IsObject(json);

    // Test cJSON_IsInvalid
    cJSON_IsInvalid(json);

    // Test cJSON_IsString
    cJSON_IsString(json);

    // Test cJSON_IsNull
    cJSON_IsNull(json);

    // Clean up
    free(buffer);
    cJSON_Delete(json);

    return 0;
}