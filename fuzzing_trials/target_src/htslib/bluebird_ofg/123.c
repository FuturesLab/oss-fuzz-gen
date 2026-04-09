#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    sam_hdr_t *hdr = NULL;
    char *header_text = NULL;

    // Ensure the data is not empty and create a null-terminated string
    if (size > 0) {
        header_text = (char *)malloc(size + 1);
        if (header_text == NULL) {
            return 0; // Memory allocation failed
        }
        memcpy(header_text, data, size);
        header_text[size] = '\0'; // Null-terminate the string

        // Parse the header text into a sam_hdr_t structure
        hdr = sam_hdr_parse(size, header_text);
        if (hdr != NULL) {
            // Call the function-under-test
            int nref = sam_hdr_nref(hdr);
            // Print or use the result if needed
            printf("Number of reference sequences: %d\n", nref);

            // Free the header structure
            sam_hdr_destroy(hdr);
        }

        // Free the allocated header text

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_parse to hts_resize_array_
        unsigned int ret_hts_features_snjhs = hts_features();
        if (ret_hts_features_snjhs < 0){
        	return 0;
        }
        char *qbuovfzi[1024] = {"bgptb", NULL};

        int ret_hts_resize_array__kwwhb = hts_resize_array_(HTS_IDX_SILENT_FAIL, (size_t )ret_hts_features_snjhs, HTS_FEATURE_CONFIGURE, (void *)hdr, qbuovfzi, BAM_FSECONDARY, (const char *)"r");
        if (ret_hts_resize_array__kwwhb < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

        free(header_text);
    }

    return 0;
}