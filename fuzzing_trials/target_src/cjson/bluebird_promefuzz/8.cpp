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
#include <cstdlib>
#include <cstring>
#include "../cJSON.h"

static cJSON* create_random_json_array(const uint8_t* Data, size_t Size) {
    cJSON* array = cJSON_CreateArray();
    if (!array) return nullptr;

    size_t index = 0;
    while (index < Size) {
        cJSON* item = cJSON_CreateNumber(Data[index] % 100);
        if (!item) {
            cJSON_Delete(array);
            return nullptr;
        }
        cJSON_AddItemToArray(array, item);
        index++;
    }
    return array;
}

static cJSON* create_random_json_item(const uint8_t* Data, size_t Size) {
    if (Size == 0) return nullptr;
    return cJSON_CreateNumber(Data[0] % 100);
}

extern "C" int LLVMFuzzerTestOneInput_8(const uint8_t *Data, size_t Size) {
    if (Size < 2) return 0;

    cJSON* json_array = create_random_json_array(Data, Size);
    if (!json_array) return 0;

    int index = Data[0] % (Size + 1);
    cJSON* new_item = create_random_json_item(Data + 1, Size - 1);

    // Test cJSON_DeleteItemFromArray
    cJSON_DeleteItemFromArray(json_array, index);

    // Test cJSON_InsertItemInArray
    if (new_item) {
        cJSON_InsertItemInArray(json_array, index, new_item);
    }

    // Test cJSON_ReplaceItemInArray
    if (new_item) {
        cJSON_ReplaceItemInArray(json_array, index, new_item);
    }

    // Test cJSON_DetachItemFromArray
    cJSON* detached_item = cJSON_DetachItemFromArray(json_array, index);

    // Test cJSON_DetachItemViaPointer
    if (detached_item) {
        cJSON* detached_via_pointer = cJSON_DetachItemViaPointer(json_array, detached_item);
        if (detached_via_pointer) {
            cJSON_Delete(detached_via_pointer);
        }
    }

    // Test cJSON_ReplaceItemViaPointer
    if (new_item) {
        cJSON_ReplaceItemViaPointer(json_array, new_item, new_item);
    }

    if (detached_item) {
        cJSON_Delete(detached_item);
    }

    cJSON_Delete(json_array);
    return 0;
}