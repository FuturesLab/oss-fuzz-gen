#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_212(const uint8_t *data, size_t size) {
    // Define and initialize variables
    hid_t loc_id = 1; // Use a valid non-negative hid_t value
    const char *old_name = "old_name";
    const char *new_name = "new_name";
    hid_t es_id = 1; // Use a valid non-negative hid_t value

    // Call the function-under-test
    herr_t result = H5Arename_async(loc_id, old_name, new_name, es_id);

    // Return 0 to indicate the fuzzer ran successfully
    return 0;
}