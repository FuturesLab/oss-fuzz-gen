#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_230(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t loc_id = 1;  // Example valid hid_t, should be a valid location ID
    const char *obj_name = "example_object";  // Example object name
    H5_index_t idx_type = H5_INDEX_NAME;  // Example index type
    H5_iter_order_t order = H5_ITER_INC;  // Example iteration order
    hsize_t n = 0;  // Example index position
    H5A_info_t ainfo;  // Attribute info structure
    hid_t lapl_id = H5P_DEFAULT;  // Link access property list

    // Ensure that the input data is not null and has a minimum size
    if (data == NULL || size < 1) {
        return 0;
    }

    // Call the function-under-test
    herr_t result = H5Aget_info_by_idx(loc_id, obj_name, idx_type, order, n, &ainfo, lapl_id);

    // Return 0 to indicate successful execution
    return 0;
}