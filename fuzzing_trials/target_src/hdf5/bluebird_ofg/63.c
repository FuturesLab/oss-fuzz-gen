#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function-under-test
    hid_t loc_id = H5Fopen("testfile.h5", H5F_ACC_RDONLY, H5P_DEFAULT);
    const char *group_name = "/"; // Root group
    H5_index_t idx_type = H5_INDEX_NAME;
    H5_iter_order_t order = H5_ITER_INC;
    hsize_t n = 0; // Start with the first attribute
    char name[256]; // Buffer to store the attribute name
    size_t buf_size = sizeof(name);
    hid_t lapl_id = H5P_DEFAULT;

    // Ensure the data size is sufficient for fuzzing
    if (size < 1) {
        H5Fclose(loc_id);
        return 0;
    }

    // Call the function-under-test
    ssize_t result = H5Aget_name_by_idx(loc_id, group_name, idx_type, order, n, name, buf_size, lapl_id);

    // Close the file
    H5Fclose(loc_id);

    return 0;
}