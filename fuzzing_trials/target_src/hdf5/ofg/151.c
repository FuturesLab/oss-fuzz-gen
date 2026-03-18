#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_151(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract the required parameters
    if (size < 2) {
        return 0;
    }

    // Extract parameters from the input data
    hid_t file_id = (hid_t)data[0]; // Use the first byte as a hid_t
    hid_t es_id = (hid_t)data[1]; // Use the second byte as a hid_t

    // Call the function-under-test
    herr_t result = H5Fclose_async(file_id, es_id);

    // Return 0 to indicate successful execution of the fuzzer
    return 0;
}