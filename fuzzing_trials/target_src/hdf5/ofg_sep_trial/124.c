#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Ensure we have enough data to create a valid hid_t
    if (size < sizeof(hid_t)) {
        H5close();
        return 0;
    }

    // Extract a hid_t from the input data
    hid_t dataset_id = *((hid_t *)data);

    // Call the function-under-test
    hsize_t storage_size = H5Dget_storage_size(dataset_id);

    // Close the HDF5 library
    H5close();

    return 0;
}