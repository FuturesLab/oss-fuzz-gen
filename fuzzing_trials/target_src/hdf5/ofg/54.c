#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Ensure size is sufficient for an hid_t
    if (size < sizeof(hid_t)) {
        H5close();
        return 0;
    }

    // Interpret the data as an hid_t
    hid_t dataset_id = *(const hid_t *)data;

    // Call the function-under-test
    hid_t dtype_id = H5Dget_type(dataset_id);

    // Close the datatype if it's valid
    if (dtype_id >= 0) {
        H5Tclose(dtype_id);
    }

    // Close HDF5 library
    H5close();

    return 0;
}