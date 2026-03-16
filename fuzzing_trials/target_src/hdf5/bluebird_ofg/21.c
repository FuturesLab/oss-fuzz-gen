#include <stdint.h>
#include <stdlib.h>
#include "hdf5.h"

herr_t gather_callback(void *src_buf, size_t src_buf_bytes, void *operator_data) {
    // Dummy callback function that does nothing
    return 0;
}

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    if (size < 10 * sizeof(int)) {
        // Ensure there is enough data to fill the buffer
        return 0;
    }

    hid_t src_space_id = H5Screate(H5S_SIMPLE);
    hid_t type_id = H5Tcopy(H5T_NATIVE_INT);
    size_t dst_buf_size = 10 * sizeof(int);
    void *dst_buf = malloc(dst_buf_size);
    void *operator_data = NULL;

    if (src_space_id < 0 || type_id < 0 || dst_buf == NULL) {
        // Cleanup and return if any initialization failed
        if (src_space_id >= 0) H5Sclose(src_space_id);
        if (type_id >= 0) H5Tclose(type_id);
        if (dst_buf != NULL) free(dst_buf);
        return 0;
    }

    // Set up a simple dataspace
    hsize_t dims[1] = {10};
    H5Sset_extent_simple(src_space_id, 1, dims, NULL);

    // Call the function under test
    H5Dgather(src_space_id, (const void *)data, type_id, dst_buf_size, dst_buf, gather_callback, operator_data);

    // Cleanup
    H5Sclose(src_space_id);
    H5Tclose(type_id);
    free(dst_buf);

    return 0;
}