#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // Include for uint8_t
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_337(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3_str *str;
    const char *input_string;
    int append_length;

    // Initialize sqlite3_str
    str = sqlite3_str_new(0);
    if (str == NULL) {
        return 0; // Memory allocation failed
    }

    // Ensure the input data is not NULL and fits within reasonable limits
    if (size > 0 && size <= 100) {
        // Create a null-terminated string from the input data
        input_string = (const char *)malloc(size + 1);
        if (input_string == NULL) {
            sqlite3_str_finish(str);
            return 0; // Memory allocation failed
        }
        memcpy((void *)input_string, data, size);
        ((char *)input_string)[size] = '\0'; // Null-terminate the string

        // Set the length of the string to append
        append_length = (int)size;

        // Call the function under test
        sqlite3_str_append(str, input_string, append_length);

        // Clean up
        free((void *)input_string);
    }

    // Finish the string and clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_str_finish to sqlite3_randomness

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_str_length with sqlite3_str_errcode
    int ret_sqlite3_str_length_cfzaf = sqlite3_str_errcode(NULL);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_sqlite3_str_length_cfzaf < 0){
    	return 0;
    }

    sqlite3_randomness(ret_sqlite3_str_length_cfzaf, (void *)str);

    // End mutation: Producer.APPEND_MUTATOR

    sqlite3_str_finish(str);

    return 0;
}