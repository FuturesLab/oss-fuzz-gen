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

extern "C" int LLVMFuzzerTestOneInput_41(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_GetObjectItemCaseSensitive to cJSON_AddNumberToObject
    void* ret_cJSON_malloc_flitj = cJSON_malloc(0);
    if (ret_cJSON_malloc_flitj == NULL){
    	return 0;
    }
    cJSON_bool ret_cJSON_IsString_aarqm = cJSON_IsString(item2);
    if (ret_cJSON_IsString_aarqm < 0){
    	return 0;
    }

    cJSON* ret_cJSON_AddNumberToObject_xvhih = cJSON_AddNumberToObject(item1, (const char *)ret_cJSON_malloc_flitj, (const double )ret_cJSON_IsString_aarqm);
    if (ret_cJSON_AddNumberToObject_xvhih == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cJSON *item4 = cJSON_GetObjectItemCaseSensitive(json, "key4");

    // Use cJSON_IsNumber to check if items are numbers

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cJSON_IsNumber with cJSON_IsArray
    if (cJSON_IsArray(item3)) {
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


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