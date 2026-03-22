#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "plist/plist.h"

extern "C" {
    // Include necessary C headers and functions here
    #include "plist/plist.h"
}

extern "C" int LLVMFuzzerTestOneInput_27(const uint8_t *data, size_t size) {
    // Initialize plist_t variable
    plist_t plist = NULL;
    
    // Create a plist from the input data
    plist_from_bin((const char*)data, size, &plist);

    // Prepare variables for plist_to_bin
    char *bin_data = NULL;
    uint32_t bin_size = 0;

    // Call the function-under-test
    plist_err_t result = plist_to_bin(plist, &bin_data, &bin_size);

    // Clean up
    if (bin_data != NULL) {
        free(bin_data);
    }

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_to_bin to plist_key_val_compare
    plist_t ret_plist_new_uid_bmjvt = plist_new_uid(-1);


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_new_uid to plist_get_string_ptr
    uint32_t ret_plist_array_get_size_rimbx = plist_array_get_size(ret_plist_new_uid_bmjvt);
    if (ret_plist_array_get_size_rimbx < 0){
    	return 0;
    }


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_array_get_size to plist_array_remove_item
    plist_t ret_plist_copy_vvohn = plist_copy(plist);

    plist_array_remove_item(ret_plist_copy_vvohn, ret_plist_array_get_size_rimbx);

    // End mutation: Producer.APPEND_MUTATOR

    const char* ret_plist_get_string_ptr_eayzg = plist_get_string_ptr(ret_plist_new_uid_bmjvt, (uint64_t *)&ret_plist_array_get_size_rimbx);
    if (ret_plist_get_string_ptr_eayzg == NULL){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    int ret_plist_key_val_compare_ebamo = plist_key_val_compare(ret_plist_new_uid_bmjvt, bin_data);
    if (ret_plist_key_val_compare_ebamo < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    plist_free(plist);

    return 0;
}