#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "plist/plist.h"

extern "C" {
    // Include necessary C headers and functions here
    #include "plist/plist.h"
}

extern "C" int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_to_bin to plist_is_binary
    uint32_t ret_plist_array_get_size_shcbp = plist_array_get_size(plist);
    if (ret_plist_array_get_size_shcbp < 0){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_array_get_size to plist_set_int_val
    plist_t ret_plist_new_bool_sgsbx = plist_new_bool(-1);

    plist_set_int_val(ret_plist_new_bool_sgsbx, (int64_t )ret_plist_array_get_size_shcbp);

    // End mutation: Producer.APPEND_MUTATOR

    int ret_plist_is_binary_zaozn = plist_is_binary(bin_data, ret_plist_array_get_size_shcbp);
    if (ret_plist_is_binary_zaozn < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    plist_free(plist);

    return 0;
}