#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_134(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t attribute_id = H5Acreate2(H5S_ALL, "attribute", H5T_NATIVE_INT, H5S_ALL, H5P_DEFAULT, H5P_DEFAULT);
    size_t buf_size = size > 0 ? size : 1; // Ensure buffer size is not zero
    char *name_buffer = (char *)malloc(buf_size);

    // Ensure name_buffer is not NULL
    if (name_buffer == NULL) {
        H5Aclose(attribute_id);
        return 0;
    }

    // Fuzz the function-under-test
    ssize_t result = H5Aget_name(attribute_id, buf_size, name_buffer);

    // Clean up
    free(name_buffer);
    H5Aclose(attribute_id);

    return 0;
}