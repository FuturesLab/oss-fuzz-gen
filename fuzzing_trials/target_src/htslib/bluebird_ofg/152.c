#include <stdint.h>
#include <stddef.h>
#include "htslib/hts.h"
#include <string.h>

// Fuzzing harness for hts_parse_format
int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
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
    hts_parse_format(&format, input_str);

    // Free allocated memory

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_parse_format to hts_format_description


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_parse_format to hts_open_format
    char* ret_hts_format_description_doqqg = hts_format_description(&format);
    if (ret_hts_format_description_doqqg == NULL){
    	return 0;
    }
    const char rwqtiikt[1024] = "jynnj";

    htsFile* ret_hts_open_format_cyzfi = hts_open_format(rwqtiikt, ret_hts_format_description_doqqg, &format);
    if (ret_hts_open_format_cyzfi == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    char* ret_hts_format_description_rsmml = hts_format_description(&format);
    if (ret_hts_format_description_rsmml == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(input_str);

    return 0;
}