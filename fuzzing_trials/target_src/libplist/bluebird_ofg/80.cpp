#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "plist/plist.h"

extern "C" {
    // Include necessary C headers and functions here
    #include "plist/plist.h"
}

extern "C" int LLVMFuzzerTestOneInput_80(const uint8_t *data, size_t size) {
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

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from plist_to_bin to plist_from_xml
    plist_t gqwmukdb;
    memset(&gqwmukdb, 0, sizeof(gqwmukdb));

    plist_err_t ret_plist_from_xml_cqgoh = plist_from_xml(bin_data, 0, &gqwmukdb);

    // End mutation: Producer.APPEND_MUTATOR

    plist_free(plist);

    return 0;
}