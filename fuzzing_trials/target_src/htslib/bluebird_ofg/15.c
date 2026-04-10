#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/tbx.h" // Include the tabix library for index functions

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of hts_open
    const char bdvkllvf[1024] = "zlkcb";
    htsFile *file = hts_open(param_str, bdvkllvf);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (file == NULL) {
        free(param_str);
        return 0; // Failed to open file
    }

    tbx_t *tbx = tbx_index_load(param_str);
    if (tbx == NULL) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with sam_idx_save

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sam_idx_save with hts_close
        hts_close(file);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        // End mutation: Producer.REPLACE_FUNC_MUTATOR



        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from hts_close to hts_crc32
        const uint8_t izpafjaw = 0;
        double ret_bam_aux2f_zcfcr = bam_aux2f(&izpafjaw);
        if (ret_bam_aux2f_zcfcr < 0){
        	return 0;
        }

        uint32_t ret_hts_crc32_knzbh = hts_crc32(FT_VCF, (const void *)file, (size_t )ret_bam_aux2f_zcfcr);
        if (ret_hts_crc32_knzbh < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        free(param_str);
        return 0; // Failed to load index
    }

    // Call a function that utilizes the index, e.g., tbx_name2id
    int result = tbx_name2id(tbx, param_str);

    // Clean up
    tbx_destroy(tbx);
    hts_close(file);
    free(param_str);

    return 0;
}