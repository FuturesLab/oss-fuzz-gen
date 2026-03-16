#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_129(const uint8_t *data, size_t size) {
    // Ensure that the input size is large enough to provide meaningful data
    if (size < sizeof(hid_t) + sizeof(hsize_t)) {
        return 0;
    }

    // Extract a valid location ID and index position from the input data
    hid_t loc_id = *((hid_t *)data);
    hsize_t n = *((hsize_t *)(data + sizeof(hid_t)));

    // Set a valid attribute name and other parameters
    const char *attr_name = "attribute_name"; // Non-NULL attribute name
    H5_index_t idx_type = H5_INDEX_NAME; // Valid index type
    H5_iter_order_t order = H5_ITER_INC; // Valid iteration order
    hid_t lapl_id = H5P_DEFAULT; // Link access property list

    // Call the function-under-test
    herr_t result = H5Adelete_by_idx(loc_id, attr_name, idx_type, order, n, lapl_id);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}