#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "plist/plist.h"

extern "C" int LLVMFuzzerTestOneInput_28(const uint8_t *data, size_t size) {
    // Initialize plist
    plist_t plist = plist_new_data((const char*)data, size);

    // Initialize variables for the function parameters
    char *data_val = (char *)malloc(size + 1);
    uint64_t length = 0;

    if (data_val == NULL) {
        plist_free(plist);
        return 0;
    }
    
    // Ensure data_val is null-terminated
    memcpy(data_val, data, size);
    data_val[size] = '\0';

    // Call the function-under-test
    plist_get_data_val(plist, &data_val, &length);

    // Clean up
    free(data_val);
    plist_free(plist);

    return 0;
}