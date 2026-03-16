#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Ensure there is enough data to read from
    if (size < sizeof(hid_t) + sizeof(hsize_t)) {
        return 0;
    }

    // Initialize variables
    hid_t dataset_id;
    hsize_t dims[1];

    // Extract dataset_id from the data
    dataset_id = *((hid_t *)data);
    data += sizeof(hid_t);
    size -= sizeof(hid_t);

    // Extract hsize_t value from the data
    dims[0] = *((hsize_t *)data);

    // Call the function-under-test
    herr_t result = H5Dset_extent(dataset_id, dims);

    // Use the result in some way (e.g., just to avoid compiler warnings)
    (void)result;

    return 0;
}