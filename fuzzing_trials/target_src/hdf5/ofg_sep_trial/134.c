#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    hid_t dataset_id = H5I_INVALID_HID; // Use a valid dataset ID
    hid_t type_id = H5T_NATIVE_INT;     // Use a valid datatype ID
    hid_t space_id = H5S_SIMPLE;        // Use a valid dataspace ID
    hsize_t buf_size = 0;               // Buffer size to be determined by the function

    // Create a dataspace with a single dimension
    hsize_t dims[1] = {size};
    space_id = H5Screate_simple(1, dims, NULL);

    // Call the function-under-test
    herr_t result = H5Dvlen_get_buf_size(dataset_id, type_id, space_id, &buf_size);

    // Ensure the result is used to prevent compiler optimizations
    (void)result;
    (void)buf_size;

    // Close the dataspace
    H5Sclose(space_id);

    return 0;
}