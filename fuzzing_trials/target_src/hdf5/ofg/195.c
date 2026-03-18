#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_195(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    hid_t loc_id = H5I_INVALID_HID;  // Initialize to an invalid ID
    hsize_t idx = 0;  // Initialize index to zero

    // Check if the input size is sufficient to extract parameters
    if (size < sizeof(hid_t) + sizeof(hsize_t)) {
        return 0;
    }

    // Extract parameters from the input data
    loc_id = *((hid_t *)data);
    idx = *((hsize_t *)(data + sizeof(hid_t)));

    // Call the function-under-test
    H5G_obj_t obj_type = H5Gget_objtype_by_idx(loc_id, idx);

    // Use obj_type in some way to avoid compiler warnings about unused variables
    (void)obj_type;

    return 0;
}