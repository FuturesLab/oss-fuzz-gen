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

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 3) { // Ensure there's enough data for key and raw JSON
        return 0;
    }

    // Split the input data into two parts for key and raw JSON string
    size_t key_size = (Data[0] % (Size - 2)) + 1; // Ensure at least 1 byte for key
    size_t raw_size = Size - key_size - 1; // Ensure at least 1 byte for raw JSON

    // Create buffers for key and raw JSON string
    char *key = new char[key_size + 1];
    char *raw = new char[raw_size + 1];

    // Copy data into key and raw, ensuring null termination
    memcpy(key, Data + 1, key_size);
    key[key_size] = '\0';

    memcpy(raw, Data + 1 + key_size, raw_size);
    raw[raw_size] = '\0';

    // Create a new cJSON object
    cJSON *json_object = cJSON_CreateObject();
    if (json_object == nullptr) {
        delete[] key;
        delete[] raw;
        return 0;
    }

    // Add raw JSON string to the object
    cJSON *new_item = cJSON_AddRawToObject(json_object, key, raw);

    // Clean up
    cJSON_Delete(json_object);
    delete[] key;
    delete[] raw;

    return 0;
}