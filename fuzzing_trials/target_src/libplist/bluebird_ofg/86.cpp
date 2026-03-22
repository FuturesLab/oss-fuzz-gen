#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "plist/plist.h"

extern "C" {
    // Include necessary C headers and functions here
    #include "plist/plist.h"
}

extern "C" int LLVMFuzzerTestOneInput_86(const uint8_t *data, size_t size) {
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
    plist_err_t result = plist_to_bin(plist, &bin_data, &bin_size);

    // Clean up
    if (bin_data != NULL) {
        free(bin_data);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_to_bin to plist_data_val_contains

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_to_bin to plist_from_bin
    uint32_t ret_plist_dict_get_size_ejalm = plist_dict_get_size(0);
    if (ret_plist_dict_get_size_ejalm < 0){
    	return 0;
    }
    plist_t ret_plist_get_parent_acrew = plist_get_parent(plist);

    plist_err_t ret_plist_from_bin_cvdna = plist_from_bin(bin_data, ret_plist_dict_get_size_ejalm, &ret_plist_get_parent_acrew);

    // End mutation: Producer.APPEND_MUTATOR

    plist_t ret_plist_new_int_ebkfr = plist_new_int(-1);
    int ret_plist_bool_val_is_true_vcaxx = plist_bool_val_is_true(plist);
    if (ret_plist_bool_val_is_true_vcaxx < 0){
    	return 0;
    }

    int ret_plist_data_val_contains_xxwzg = plist_data_val_contains(ret_plist_new_int_ebkfr, (const uint8_t *)&ret_plist_bool_val_is_true_vcaxx, (size_t )bin_size);
    if (ret_plist_data_val_contains_xxwzg < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    plist_free(plist);

    return 0;
}