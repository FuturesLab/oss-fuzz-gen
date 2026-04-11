#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Initialize parameters for sam_hdr_remove_lines
    sam_hdr_t *hdr = sam_hdr_init();
    const char *type = "SQ";  // Example type, can vary
    const char *key = "SN";   // Example key, can vary
    void *iter = NULL;        // Example iterator, can vary

    // Ensure the data is not empty
    if (size == 0) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Create a temporary copy of the data to use as a header text

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_init to sam_hdr_add_pg
    const char anmpittl[1024] = "kglip";

    int ret_sam_hdr_add_pg_kfyaf = sam_hdr_add_pg(hdr, anmpittl);
    if (ret_sam_hdr_add_pg_kfyaf < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    char *header_text = (char *)malloc(size + 1);
    if (header_text == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(header_text, data, size);
    header_text[size] = '\0';

    // Try to parse the header from the data
    if (sam_hdr_add_lines(hdr, header_text, 0) < 0) {
        free(header_text);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Call the function-under-test
    sam_hdr_remove_lines(hdr, type, key, iter);

    // Clean up

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_remove_lines to sam_hdr_tid2len
    size_t ret_sam_hdr_length_ubtvb = sam_hdr_length(hdr);
    if (ret_sam_hdr_length_ubtvb < 0){
    	return 0;
    }

    hts_pos_t ret_sam_hdr_tid2len_qpoqk = sam_hdr_tid2len(hdr, (int )ret_sam_hdr_length_ubtvb);
    if (ret_sam_hdr_tid2len_qpoqk < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    free(header_text);
    sam_hdr_destroy(hdr);

    return 0;
}