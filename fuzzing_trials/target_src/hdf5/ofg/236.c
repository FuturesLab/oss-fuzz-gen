#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>  // Ensure the HDF5 library is included

int LLVMFuzzerTestOneInput_236(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t attr_id = 1; // Assuming a valid non-zero hid_t, as 0 is often invalid
    const char *attr_name = "test_attribute";

    // Call the function-under-test
    htri_t result = H5Aexists(attr_id, attr_name);

    // Use the result in some way to avoid compiler optimizations
    if (result < 0) {
        // Handle error if needed
    }

    return 0;
}