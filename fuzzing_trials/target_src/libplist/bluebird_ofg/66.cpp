#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "plist/plist.h"

extern "C" {
    // Include necessary C headers and functions here
    #include "plist/plist.h"
}

extern "C" int LLVMFuzzerTestOneInput_66(const uint8_t *data, size_t size) {
    // Initialize plist_t variable
    plist_t plist = NULL;
    
    // Create a plist from the input data

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function plist_from_bin with plist_from_xml
    plist_from_xml((const char*)data, size, &plist);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    // Prepare variables for plist_to_bin
    char *bin_data = NULL;
    uint32_t bin_size = 0;

    // Call the function-under-test

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_from_xml to plist_uint_val_compare
    int ret_plist_bool_val_is_true_htdzr = plist_bool_val_is_true(plist);
    if (ret_plist_bool_val_is_true_htdzr < 0){
    	return 0;
    }

    int ret_plist_uint_val_compare_tzmdy = plist_uint_val_compare(plist, (uint64_t )ret_plist_bool_val_is_true_htdzr);
    if (ret_plist_uint_val_compare_tzmdy < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    plist_err_t result = plist_to_bin(plist, &bin_data, &bin_size);

    // Clean up
    if (bin_data != NULL) {
        free(bin_data);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_to_bin to plist_get_string_val
    plist_t ret_plist_new_uint_ppfnb = plist_new_uint(size);

    plist_get_string_val(ret_plist_new_uint_ppfnb, &bin_data);

    // End mutation: Producer.APPEND_MUTATOR

    plist_free(plist);

    return 0;
}