#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t attribute_id = 1; // Assuming a valid attribute ID for testing
    const char *old_name = "old_name";
    const char *new_name = "new_name";

    // Call the function-under-test
    herr_t result = H5Arename(attribute_id, old_name, new_name);

    // Use the result to avoid compiler warnings (if any)
    (void)result;

    return 0;
}