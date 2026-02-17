#include <stdint.h>
#include <stdlib.h>

#include "../cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_1(const uint8_t *data, size_t size) {
    if (size < sizeof(int) || size % sizeof(int) != 0) {
        return 0;
    }

    int array_size = size / sizeof(int);
    int *array = (int *)data;

    cJSON *json_array = cJSON_CreateIntArray(array, array_size);

    if (json_array != NULL) {

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_AddItemToObjectCS
        void* ret_cJSON_malloc_mnasn = cJSON_malloc(CJSON_VERSION_MINOR);
        if (ret_cJSON_malloc_mnasn == NULL){
        	return 0;
        }
        cJSON* ret_cJSON_CreateString_sipqo = cJSON_CreateString((const char *)"r");
        if (ret_cJSON_CreateString_sipqo == NULL){
        	return 0;
        }

        cJSON_bool ret_cJSON_AddItemToObjectCS_rbkus = cJSON_AddItemToObjectCS(json_array, (const char *)ret_cJSON_malloc_mnasn, ret_cJSON_CreateString_sipqo);
        if (ret_cJSON_AddItemToObjectCS_rbkus < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        cJSON_Delete(json_array);
    }
    return 0;
}