#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_108(const uint8_t *data, size_t size) {
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
    free(header_text);
    sam_hdr_destroy(hdr);

    
    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_hdr_destroy to sam_itr_regions
    const uint8_t jhssabsh = 64;
    int64_t ret_bam_aux2i_ipkcx = bam_aux2i(&jhssabsh);
    if (ret_bam_aux2i_ipkcx < 0){
    	return 0;
    }
    hts_reglist_t ccojpvcl;
    memset(&ccojpvcl, 0, sizeof(ccojpvcl));

    hts_itr_t* ret_sam_itr_regions_ekvfw = sam_itr_regions(NULL, hdr, &ccojpvcl, (unsigned int )ret_bam_aux2i_ipkcx);
    if (ret_sam_itr_regions_ekvfw == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

return 0;
}