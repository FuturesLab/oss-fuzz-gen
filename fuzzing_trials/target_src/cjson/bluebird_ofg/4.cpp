#include <stdint.h>
#include <stdlib.h>

#include "../cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    if (size < sizeof(int) || size % sizeof(int) != 0) {
        return 0;
    }

    int array_size = size / sizeof(int);
    int *array = (int *)data;

    cJSON *json_array = cJSON_CreateIntArray(array, array_size);

    if (json_array != NULL) {

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_AddItemToObjectCS
        const char pcfyvlck[1024] = "tasfv";
        cJSON* ret_cJSON_CreateStringReference_pipju = cJSON_CreateStringReference(pcfyvlck);
        if (ret_cJSON_CreateStringReference_pipju == NULL){
        	return 0;
        }

        cJSON_bool ret_cJSON_AddItemToObjectCS_zafuc = cJSON_AddItemToObjectCS(json_array, (const char *)data, ret_cJSON_CreateStringReference_pipju);
        if (ret_cJSON_AddItemToObjectCS_zafuc < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        cJSON_Delete(json_array);
    }
    return 0;
}