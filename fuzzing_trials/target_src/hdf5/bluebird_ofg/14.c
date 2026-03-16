#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Initialize source and destination buffers
    void *src_buf = malloc(size);
    void *dst_buf = malloc(size);

    // Copy data to source buffer
    if (src_buf != NULL) {
        memcpy(src_buf, data, size);
    }

    // Create a simple memory datatype
    hid_t src_type = H5Tcopy(H5T_NATIVE_INT);
    hid_t dst_type = H5Tcopy(H5T_NATIVE_INT);

    // Create a dataspace
    hsize_t dims[1] = {size / sizeof(int)};
    hid_t space_id = H5Screate_simple(1, dims, NULL);

    // Call the function-under-test
    if (src_buf != NULL && dst_buf != NULL) {
        H5Dfill(src_buf, src_type, dst_buf, dst_type, space_id);
    }

    // Clean up
    if (src_buf != NULL) {
        free(src_buf);
    }
    if (dst_buf != NULL) {
        free(dst_buf);
    }
    H5Tclose(src_type);
    H5Tclose(dst_type);
    H5Sclose(space_id);

    return 0;
}