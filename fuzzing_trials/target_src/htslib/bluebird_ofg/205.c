#include <stdint.h>
#include <stddef.h>
#include "htslib/hts.h"
#include <string.h>

// Fuzzing harness for hts_parse_format
int LLVMFuzzerTestOneInput_205(const uint8_t *data, size_t size) {
    // Ensure the input size is non-zero
    if (size == 0) {
        return 0;
    }

    // Allocate and initialize htsFormat structure
    htsFormat format;
    memset(&format, 0, sizeof(htsFormat));

    // Ensure null-terminated string for the second parameter
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';  // Null-terminate the string

    // Call the function-under-test

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_parse_format with hts_parse_opt_list
    hts_parse_opt_list(&format, input_str);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Free allocated memory

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_parse_format to hts_format_description

    char* ret_hts_format_description_rsmml = hts_format_description(&format);
    if (ret_hts_format_description_rsmml == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(input_str);

    return 0;
}