#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_158(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract a valid hid_t
    if (data == NULL || size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t from the input data
    hid_t dataset_id = *((hid_t *)data);

    // Call the function-under-test
    herr_t result = H5Dflush(dataset_id);

    // Handle the result if necessary (for fuzzing, we typically don't need to)
    (void)result; // Suppress unused variable warning

    return 0;
}