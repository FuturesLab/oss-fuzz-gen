#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <plist/plist.h>

extern "C" int LLVMFuzzerTestOneInput_168(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated before passing it to plist_new_string
    char *null_terminated_data = (char *)malloc(size + 1);
    if (null_terminated_data == NULL) {
        return 0; // Exit if memory allocation fails
    }
    
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0'; // Null-terminate the string

    // Check if the input data is not empty to ensure the function under test is meaningfully invoked
    if (size > 0) {
        // Call the function-under-test
        plist_t plist = plist_new_string(null_terminated_data);

        // Free the plist object if it was created successfully
        if (plist != NULL) {
            plist_free(plist);
        }
    }

    // Free allocated memory
    free(null_terminated_data);

    return 0;
}