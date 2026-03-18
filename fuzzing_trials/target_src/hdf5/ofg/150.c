#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_150(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for our needs
    if (size < 3) {
        return 0;
    }

    // Initialize parameters for H5Fclose_async
    unsigned int app_line = (unsigned int)data[0];
    hid_t file_id = (hid_t)data[1];
    hid_t es_id = (hid_t)data[2];

    // Call the function-under-test
    herr_t result = H5Fclose_async(file_id, es_id);

    // Return 0 to indicate the fuzzer can continue
    return 0;
}