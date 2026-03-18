#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_210(const uint8_t *data, size_t size) {
    // Ensure there is enough data for the strings and other parameters
    if (size < 12) {
        return 0;
    }

    // Extract strings and parameters from the input data
    hid_t loc_id = (hid_t)data[0];
    const char *old_name = (const char *)(data + 1);
    const char *new_name = (const char *)(data + 2);
    hid_t es_id = (hid_t)data[3];

    // Call the function-under-test
    herr_t result = H5Arename_async(loc_id, old_name, new_name, es_id);

    // The actual result of the function is not important for fuzzing
    (void)result;

    return 0;
}