#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_26(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    hid_t loc_id = H5I_INVALID_HID;
    const char *obj_name = "test_object";
    H5_index_t idx_type = H5_INDEX_NAME;
    H5_iter_order_t order = H5_ITER_INC;
    hsize_t n = 0;
    char name[256];
    size_t buf_size = sizeof(name);
    hid_t lapl_id = H5P_DEFAULT;

    // Ensure the data size is sufficient for fuzzing
    if (size < sizeof(hsize_t)) {
        return 0;
    }

    // Use the data to influence the 'n' parameter
    memcpy(&n, data, sizeof(hsize_t));

    // Call the function-under-test
    ssize_t result = H5Aget_name_by_idx(loc_id, obj_name, idx_type, order, n, name, buf_size, lapl_id);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}