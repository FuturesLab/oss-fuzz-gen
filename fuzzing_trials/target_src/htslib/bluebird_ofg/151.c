#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/tbx.h" // Include the tabix library for index functions

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient for our needs
    if (size < 5) {
        return 0;
    }

    // Use the first byte of data as an integer parameter
    int param_int = (int)data[0];

    // Use the rest of the data as a string, ensuring it's null-terminated
    size_t string_size = size - 1;
    char *param_str = (char *)malloc(string_size + 1);
    if (param_str == NULL) {
        return 0; // Memory allocation failed
    }
    memcpy(param_str, data + 1, string_size);
    param_str[string_size] = '\0';

    // Initialize htsFile and tbx_t structures
    htsFile *file = hts_open(param_str, "r");
    if (file == NULL) {
        free(param_str);
        return 0; // Failed to open file
    }

    tbx_t *tbx = tbx_index_load(param_str);
    if (tbx == NULL) {
        hts_close(file);
        free(param_str);
        return 0; // Failed to load index
    }

    // Call a function that utilizes the index, e.g., tbx_name2id
    int result = tbx_name2id(tbx, param_str);

    // Clean up
    tbx_destroy(tbx);

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with hts_flush
    hts_flush(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    free(param_str);

    return 0;
}