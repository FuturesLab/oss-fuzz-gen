#include <stdint.h>
#include <stdlib.h>

#include "../cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_2(const uint8_t *data, size_t size) {
    if (size < sizeof(int) || size % sizeof(int) != 0) {
        return 0;
    }

    int array_size = size / sizeof(int);
    int *array = (int *)data;

    cJSON *json_array = cJSON_CreateIntArray(array, array_size);

    if (json_array != NULL) {

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_AddItemToObjectCS
        cJSON* ret_cJSON_CreateNumber_jehih = cJSON_CreateNumber(cJSON_String);
        if (ret_cJSON_CreateNumber_jehih == NULL){
        	return 0;
        }
        char* ret_cJSON_GetStringValue_tyglw = cJSON_GetStringValue(json_array);
        if (ret_cJSON_GetStringValue_tyglw == NULL){
        	return 0;
        }

        cJSON_bool ret_cJSON_AddItemToObjectCS_lkpya = cJSON_AddItemToObjectCS(ret_cJSON_CreateNumber_jehih, ret_cJSON_GetStringValue_tyglw, json_array);
        if (ret_cJSON_AddItemToObjectCS_lkpya < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        cJSON_Delete(json_array);
    }
    return 0;
}