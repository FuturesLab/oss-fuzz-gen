#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <hdf5.h>

herr_t gather_callback(const void *elem, void *operator_data) {
    // Example callback function for H5Dgather
    // Simply return 0 for this example
    return 0;
}

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    if (size < sizeof(int)) {
        // Not enough data to proceed
        return 0;
    }

    // Create a simple dataspace with a single element
    hsize_t dims[1] = {1};
    hid_t src_space_id = H5Screate_simple(1, dims, NULL);
    if (src_space_id < 0) {
        return 0;
    }

    // Create a datatype, e.g., native integer
    hid_t type_id = H5Tcopy(H5T_NATIVE_INT);
    if (type_id < 0) {
        H5Sclose(src_space_id);
        return 0;
    }

    size_t dst_buf_size = sizeof(int); // Define a buffer size for one integer
    void *dst_buf = malloc(dst_buf_size); // Allocate memory for destination buffer
    if (dst_buf == NULL) {
        H5Tclose(type_id);
        H5Sclose(src_space_id);
        return 0;
    }

    void *operator_data = NULL; // Example operator data, can be NULL

    // Call the function-under-test
    herr_t status = H5Dgather(src_space_id, data, type_id, dst_buf_size, dst_buf, gather_callback, operator_data);

    // Check the status if needed
    if (status < 0) {
        // Handle error
    }

    // Clean up
    free(dst_buf);
    H5Tclose(type_id);
    H5Sclose(src_space_id);

    return 0;
}