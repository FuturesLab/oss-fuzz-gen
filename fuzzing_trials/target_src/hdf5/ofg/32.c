#include <stdint.h>
#include <string.h> // Include string.h for memcpy
#include <hdf5.h>

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Initialize the HDF5 library
    H5open();

    // Extract a hid_t from the input data
    hid_t dataset_id;
    memcpy(&dataset_id, data, sizeof(hid_t));

    // Call the function-under-test
    haddr_t offset = H5Dget_offset(dataset_id);

    // Perform any necessary cleanup
    // (In this case, there is no specific cleanup required for H5Dget_offset)

    // Close the HDF5 library
    H5close();

    return 0;
}