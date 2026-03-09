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

extern "C" int LLVMFuzzerTestOneInput_33(const uint8_t *Data, size_t Size) {
    if (Size == 0) {
        return 0;
    }

    // Convert input data to a null-terminated string
    char *jsonString = (char *)malloc(Size + 1);
    if (!jsonString) {
        return 0;
    }
    memcpy(jsonString, Data, Size);
    jsonString[Size] = '\0';

    // Parse the JSON string
    cJSON *json = cJSON_Parse(jsonString);
    if (!json) {
        const char *errorPtr = cJSON_GetErrorPtr();
        // Handle parse error if needed
        free(jsonString);
        return 0;
    }

    // Use cJSON_GetObjectItemCaseSensitive to retrieve items
    cJSON *item1 = cJSON_GetObjectItemCaseSensitive(json, "key1");
    if (cJSON_IsString(item1)) {
        // Do something with the string
    }

    cJSON *item2 = cJSON_GetObjectItemCaseSensitive(json, "key2");
    cJSON *item3 = cJSON_GetObjectItemCaseSensitive(json, "key3");
    cJSON *item4 = cJSON_GetObjectItemCaseSensitive(json, "key4");

    // Use cJSON_IsNumber to check if items are numbers

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_GetObjectItemCaseSensitive to cJSON_AddItemReferenceToObject
    cJSON* ret_cJSON_CreateObjectReference_siqml = cJSON_CreateObjectReference(item4);
    if (ret_cJSON_CreateObjectReference_siqml == NULL){
    	return 0;
    }

    cJSON_bool ret_cJSON_AddItemReferenceToObject_wgnbn = cJSON_AddItemReferenceToObject(item1, (const char *)"w", ret_cJSON_CreateObjectReference_siqml);
    if (ret_cJSON_AddItemReferenceToObject_wgnbn < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    if (cJSON_IsNumber(item3)) {
        // Do something with the number
    }

    if (cJSON_IsNumber(item4)) {
        // Do something with the number
    }

    // Clean up
    cJSON_Delete(json);
    free(jsonString);

    return 0;
}