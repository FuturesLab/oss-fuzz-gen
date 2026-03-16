#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_197(const uint8_t *data, size_t size) {
    // Ensure that size is at least the size of an hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Initialize the HDF5 library
    H5open();

    // Extract an hid_t from the input data
    hid_t file_id = *(hid_t *)data;

    // Allocate memory for the file number
    unsigned long file_no = 0;

    // Call the function-under-test
    herr_t status = H5Fget_fileno(file_id, &file_no);

    // Clean up and close the HDF5 library
    H5close();

    return 0;
}