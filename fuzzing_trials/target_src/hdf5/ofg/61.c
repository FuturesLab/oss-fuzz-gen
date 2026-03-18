#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_61(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for creating an hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Initialize HDF5 library
    H5open();

    // Extract hid_t from the input data
    hid_t dataset_id = *(const hid_t *)data;

    // Initialize H5D_space_status_t variable
    H5D_space_status_t space_status;

    // Call the function-under-test
    herr_t status = H5Dget_space_status(dataset_id, &space_status);

    // Perform any necessary cleanup
    H5close();

    return 0;
}