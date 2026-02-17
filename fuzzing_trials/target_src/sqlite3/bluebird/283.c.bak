#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // Include for uint8_t
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_283(const uint8_t *data, size_t size) {
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


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_str_new to sqlite3_str_append
    int ret_sqlite3_backup_finish_kgsim = sqlite3_backup_finish(NULL);
    if (ret_sqlite3_backup_finish_kgsim < 0){
    	return 0;
    }

    sqlite3_str_append(str, (const char *)"r", ret_sqlite3_backup_finish_kgsim);

    // End mutation: Producer.APPEND_MUTATOR

    sqlite3_randomness(1, (void *)str);

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_str_finish to sqlite3_complete16


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_randomness to sqlite3_strnicmp

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_randomness to sqlite3_open_v2
    sqlite3 *afvyolwg;
    memset(&afvyolwg, 0, sizeof(afvyolwg));

    int ret_sqlite3_open_v2_ikqbl = sqlite3_open_v2((const char *)"r", &afvyolwg, 1, str);
    if (ret_sqlite3_open_v2_ikqbl < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_stmt_readonly with sqlite3_step

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_open_v2 to sqlite3_column_double

    double ret_sqlite3_column_double_cdbhh = sqlite3_column_double(NULL, ret_sqlite3_open_v2_ikqbl);
    if (ret_sqlite3_column_double_cdbhh < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_sqlite3_stmt_readonly_yvbul = sqlite3_step(NULL);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_sqlite3_stmt_readonly_yvbul < 0){
    	return 0;
    }
    const char ucpvztwc[1024] = "npxco";

    int ret_sqlite3_strnicmp_pwhql = sqlite3_strnicmp(ucpvztwc, str, ret_sqlite3_stmt_readonly_yvbul);
    if (ret_sqlite3_strnicmp_pwhql < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_sqlite3_complete16_qvhnw = sqlite3_complete16((const void *)str);
    if (ret_sqlite3_complete16_qvhnw < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR


            // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_str_finish to sqlite3_complete16


            // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_complete16
            int ret_sqlite3_complete16_mfhsq = sqlite3_complete16((const void *)data);
            // End mutation: Producer.REPLACE_ARG_MUTATOR


            if (ret_sqlite3_complete16_mfhsq < 0){
            	return 0;
            }

            // End mutation: Producer.APPEND_MUTATOR

    sqlite3_str_finish(str);

    return 0;
}