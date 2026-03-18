#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // Include stdlib.h for malloc and free
#include <hdf5.h>

// Define a simple gather function
herr_t gather_func(void *elem, hid_t type_id, unsigned ndim, const hsize_t *point, void *operator_data) {
    // This function could process the gathered data in some way
    // For this example, we'll just return 0 to indicate success
    return 0;
}

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Initialize the HDF5 library
    H5open();

    // Define variables for the function parameters
    hid_t dset_id = 1; // Assuming a valid dataset ID
    const void *space = data; // Use the fuzzer data as the space
    hid_t type_id = 1; // Assuming a valid datatype ID
    size_t nelmts = size / sizeof(int); // Number of elements to gather
    void *buf = malloc(size); // Allocate buffer for gathered data
    H5D_gather_func_t op = gather_func; // Use the defined gather function
    void *op_data = NULL; // No additional data needed for the gather function

    // Call the function-under-test
    herr_t status = H5Dgather(dset_id, space, type_id, nelmts, buf, op, op_data);

    // Clean up
    free(buf);

    // Close the HDF5 library
    H5close();

    return 0;
}