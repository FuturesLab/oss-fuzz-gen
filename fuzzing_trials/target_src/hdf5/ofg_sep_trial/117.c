#include <stdint.h>
#include <string.h>  // For memcpy
#include <hdf5.h>

int LLVMFuzzerTestOneInput_117(const uint8_t *data, size_t size) {
    // Ensure the size is appropriate for an hid_t, which is typically a 32 or 64-bit integer
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Initialize the HDF5 library
    H5open();

    // Extract an hid_t from the input data
    hid_t dataset_id;
    memcpy(&dataset_id, data, sizeof(hid_t));

    // Call the function-under-test
    hid_t dataspace_id = H5Dget_space(dataset_id);

    // Perform cleanup if dataspace_id is valid
    if (dataspace_id >= 0) {
        H5Sclose(dataspace_id);
    }

    // Close the HDF5 library
    H5close();

    return 0;
}