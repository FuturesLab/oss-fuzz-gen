#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_245(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract an hid_t from the data
    hid_t dataset_id = *(const hid_t *)data;

    // Call the function-under-test
    herr_t result = H5Dclose(dataset_id);

    // Use the result to prevent compiler optimizations that could skip the call
    if (result != 0) {
        // Handle error if necessary, but for fuzzing, just ensure the call is made
    }

    return 0;
}