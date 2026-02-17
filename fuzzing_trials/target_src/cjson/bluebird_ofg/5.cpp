#include <stdint.h>
#include <stdlib.h>

#include "../cJSON.h"

extern "C" int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    if (size < sizeof(int) || size % sizeof(int) != 0) {
        return 0;
    }

    int array_size = size / sizeof(int);
    int *array = (int *)data;

    cJSON *json_array = cJSON_CreateIntArray(array, array_size);

    if (json_array != NULL) {

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_Delete to cJSON_AddItemToObjectCS
        cJSON* ret_cJSON_CreateNumber_kafyq = cJSON_CreateNumber(CJSON_NESTING_LIMIT);
        if (ret_cJSON_CreateNumber_kafyq == NULL){
        	return 0;
        }
        void* ret_cJSON_malloc_xnpyb = cJSON_malloc(CJSON_CIRCULAR_LIMIT);
        if (ret_cJSON_malloc_xnpyb == NULL){
        	return 0;
        }

        cJSON_bool ret_cJSON_AddItemToObjectCS_siriq = cJSON_AddItemToObjectCS(ret_cJSON_CreateNumber_kafyq, (const char *)ret_cJSON_malloc_xnpyb, json_array);
        if (ret_cJSON_AddItemToObjectCS_siriq < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        cJSON_Delete(json_array);
    }
    return 0;
}