#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include "../cJSON.h"
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <limits>
#include <climits>

extern "C" int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(double)) {
        return 0;
    }

    // Extract a double value from the input data
    double number;
    std::memcpy(&number, Data, sizeof(double));

    // Test cJSON_CreateNumber
    cJSON *number_item = cJSON_CreateNumber(number);
    if (number_item != nullptr) {
        // Test cJSON_GetNumberValue
        double retrieved_number = cJSON_GetNumberValue(number_item);
        (void)retrieved_number; // Use the value to avoid unused variable warning

        // Test cJSON_SetNumberHelper
        double new_number = number + 1.0;
        double set_number_result = cJSON_SetNumberHelper(number_item, new_number);
        (void)set_number_result; // Use the value to avoid unused variable warning

        // Test cJSON_IsNumber
        cJSON_bool is_number = cJSON_IsNumber(number_item);
        (void)is_number; // Use the value to avoid unused variable warning

        // Clean up
        cJSON_Delete(number_item);
    }

    // Prepare data for cJSON_CreateDoubleArray
    size_t double_array_size = Size / sizeof(double);
    if (double_array_size > 0) {
        double *double_array = static_cast<double *>(std::malloc(double_array_size * sizeof(double)));
        if (double_array != nullptr) {
            std::memcpy(double_array, Data, double_array_size * sizeof(double));
            cJSON *double_array_item = cJSON_CreateDoubleArray(double_array, static_cast<int>(double_array_size));
            if (double_array_item != nullptr) {
                cJSON_Delete(double_array_item);
            }
            std::free(double_array);
        }
    }

    // Prepare data for cJSON_CreateIntArray
    size_t int_array_size = Size / sizeof(int);
    if (int_array_size > 0) {
        int *int_array = static_cast<int *>(std::malloc(int_array_size * sizeof(int)));
        if (int_array != nullptr) {
            std::memcpy(int_array, Data, int_array_size * sizeof(int));
            cJSON *int_array_item = cJSON_CreateIntArray(int_array, static_cast<int>(int_array_size));
            if (int_array_item != nullptr) {
                cJSON_Delete(int_array_item);
            }

            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from cJSON_CreateIntArray to cJSON_AddObjectToObject


            // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function cJSON_AddObjectToObject with cJSON_AddArrayToObject
            cJSON* ret_cJSON_AddObjectToObject_jthok = cJSON_AddArrayToObject(int_array_item, NULL);
            // End mutation: Producer.REPLACE_FUNC_MUTATOR


            if (ret_cJSON_AddObjectToObject_jthok == NULL){
            	return 0;
            }

            // End mutation: Producer.APPEND_MUTATOR

            std::free(int_array);
        }   }

    return 0;
}