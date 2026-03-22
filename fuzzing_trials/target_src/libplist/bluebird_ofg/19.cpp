#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "plist/plist.h"

extern "C" {
    // Include necessary C headers and functions here
    #include "plist/plist.h"
}

extern "C" int LLVMFuzzerTestOneInput_19(const uint8_t *data, size_t size) {
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
    plist_t ret_plist_dict_item_get_key_yecnw = plist_dict_item_get_key(0);
    int ret_plist_int_val_is_negative_udsuy = plist_int_val_is_negative(plist);
    if (ret_plist_int_val_is_negative_udsuy < 0){
    	return 0;
    }

    int ret_plist_data_val_contains_apwke = plist_data_val_contains(ret_plist_dict_item_get_key_yecnw, (const uint8_t *)&ret_plist_int_val_is_negative_udsuy, (size_t )bin_size);
    if (ret_plist_data_val_contains_apwke < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    plist_free(plist);

    return 0;
}