#include <stdint.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t dataset_id;

    // Check if the size is sufficient to derive a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Derive a hid_t from the input data
    dataset_id = *((hid_t *)data);

    // Call the function-under-test
    herr_t status = H5Dclose(dataset_id);

    // Return 0 to indicate successful execution
    return 0;
}