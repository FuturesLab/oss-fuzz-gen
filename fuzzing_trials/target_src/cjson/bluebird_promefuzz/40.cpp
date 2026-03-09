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

extern "C" int LLVMFuzzerTestOneInput_40(const uint8_t *Data, size_t Size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_GetObjectItemCaseSensitive to cJSON_AddStringToObject
    void* ret_cJSON_malloc_vybud = cJSON_malloc(0);
    if (ret_cJSON_malloc_vybud == NULL){
    	return 0;
    }
    void* ret_cJSON_malloc_abjyh = cJSON_malloc(CJSON_CIRCULAR_LIMIT);
    if (ret_cJSON_malloc_abjyh == NULL){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_malloc to cJSON_AddRawToObject
    cJSON* ret_cJSON_CreateArrayReference_rwhai = cJSON_CreateArrayReference(NULL);
    if (ret_cJSON_CreateArrayReference_rwhai == NULL){
    	return 0;
    }

    cJSON* ret_cJSON_AddRawToObject_hybnw = cJSON_AddRawToObject(ret_cJSON_CreateArrayReference_rwhai, NULL, (const char *)ret_cJSON_malloc_abjyh);
    if (ret_cJSON_AddRawToObject_hybnw == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cJSON* ret_cJSON_AddStringToObject_ivdvg = cJSON_AddStringToObject(item2, (const char *)ret_cJSON_malloc_vybud, (const char *)ret_cJSON_malloc_abjyh);
    if (ret_cJSON_AddStringToObject_ivdvg == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    cJSON *item3 = cJSON_GetObjectItemCaseSensitive(json, "key3");
    cJSON *item4 = cJSON_GetObjectItemCaseSensitive(json, "key4");

    // Use cJSON_IsNumber to check if items are numbers
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