#include <stdint.h>
#include <stdlib.h>

#include "../cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    if (size < sizeof(int) || size % sizeof(int) != 0) {
        return 0;
    }

    int array_size = size / sizeof(int);
    int *array = (int *)data;

    cJSON *json_array = cJSON_CreateIntArray(array, array_size);

    if (json_array != NULL) {

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_AddItemToObjectCS
        cJSON* ret_cJSON_CreateBool_gzcds = cJSON_CreateBool(CJSON_VERSION_MAJOR);
        if (ret_cJSON_CreateBool_gzcds == NULL){
        	return 0;
        }

        cJSON_bool ret_cJSON_AddItemToObjectCS_rntit = cJSON_AddItemToObjectCS(ret_cJSON_CreateBool_gzcds, NULL, json_array);
        if (ret_cJSON_AddItemToObjectCS_rntit < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        cJSON_Delete(json_array);
    }
    return 0;
}