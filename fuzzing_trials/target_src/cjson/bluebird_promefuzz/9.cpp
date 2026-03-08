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

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_GetObjectItemCaseSensitive to cJSON_PrintPreallocated
    void* ret_cJSON_malloc_rhwmo = cJSON_malloc(CJSON_NESTING_LIMIT);
    if (ret_cJSON_malloc_rhwmo == NULL){
    	return 0;
    }
    int ret_cJSON_GetArraySize_cusfi = cJSON_GetArraySize(item1);
    if (ret_cJSON_GetArraySize_cusfi < 0){
    	return 0;
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_GetArraySize to cJSON_Compare
    cJSON* ret_cJSON_CreateStringReference_wcyvp = cJSON_CreateStringReference((const char *)Data);
    if (ret_cJSON_CreateStringReference_wcyvp == NULL){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of cJSON_Compare
    cJSON_bool ret_cJSON_Compare_qohyr = cJSON_Compare(json, json, ret_cJSON_GetArraySize_cusfi);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_cJSON_Compare_qohyr < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cJSON_bool ret_cJSON_IsFalse_kkfic = cJSON_IsFalse(NULL);
    if (ret_cJSON_IsFalse_kkfic < 0){
    	return 0;
    }

    cJSON_bool ret_cJSON_PrintPreallocated_fvzkb = cJSON_PrintPreallocated(item1, (char *)ret_cJSON_malloc_rhwmo, ret_cJSON_GetArraySize_cusfi, ret_cJSON_IsFalse_kkfic);
    if (ret_cJSON_PrintPreallocated_fvzkb < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cJSON *item3 = cJSON_GetObjectItemCaseSensitive(json, "key3");
    cJSON *item4 = cJSON_GetObjectItemCaseSensitive(json, "key4");

    // Use cJSON_IsNumber to check if items are numbers

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cJSON_IsNumber with cJSON_IsRaw
    if (cJSON_IsRaw(item3)) {
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