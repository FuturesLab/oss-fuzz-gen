#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for the parameters
    if (size < 3) {
        return 0;
    }

    // Initialize parameters for H5Fclose_async
    hid_t file_id = (hid_t)data[0];
    hid_t es_id = (hid_t)data[1];

    // Call the function-under-test
    herr_t result = H5Fclose_async(file_id, es_id);

    // Use the result if needed (for debugging, logging, etc.)
    // For now, we'll just return 0 to indicate successful execution of the fuzzer
    (void)result; // Suppress unused variable warning

    return 0;
}