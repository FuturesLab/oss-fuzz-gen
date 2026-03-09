#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include "../cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_16(const uint8_t *Data, size_t Size) {
    if (Size < 2) {
        return 0;
    } // Not enough data

    // Create a JSON object from the input data
    cJSON *json = cJSON_ParseWithLength((const char*)Data, Size);
    if (json == nullptr) {
        return 0;
    } // Failed to parse JSON

    // Extract a key from the input data
    size_t keyLength = Data[0] % (Size - 1) + 1; // Ensure non-zero key length
    char *key = new char[keyLength + 1];
    memcpy(key, Data + 1, keyLength);
    key[keyLength] = '\0';

    // Create a new item to replace in the JSON object
    cJSON *newItem = cJSON_CreateString("new_value");

    // Invoke target API functions
    cJSON_DeleteItemFromObjectCaseSensitive(json, key);
    cJSON *detachedItem = cJSON_DetachItemFromObject(json, key);
    cJSON_bool hasItem = cJSON_HasObjectItem(json, key);
    cJSON_bool replaceResult = cJSON_ReplaceItemInObject(json, key, newItem);
    cJSON *detachedItemCaseSensitive = cJSON_DetachItemFromObjectCaseSensitive(json, key);
    cJSON_DeleteItemFromObject(json, key);

    // Clean up
    cJSON_Delete(json);
    if (detachedItem) {
        cJSON_Delete(detachedItem);
    }
    if (detachedItemCaseSensitive) {
        cJSON_Delete(detachedItemCaseSensitive);
    }
    if (!replaceResult) {

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_GetObjectItemCaseSensitive

        cJSON* ret_cJSON_GetObjectItemCaseSensitive_crdnq = cJSON_GetObjectItemCaseSensitive(detachedItem, NULL);
        if (ret_cJSON_GetObjectItemCaseSensitive_crdnq == NULL){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        cJSON_Delete(newItem);
    }// Free newItem if it wasn't used
    delete[] key;

    return 0;
}