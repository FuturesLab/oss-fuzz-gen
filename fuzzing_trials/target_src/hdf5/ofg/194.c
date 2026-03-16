#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_194(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function call
    hid_t group_id = H5I_INVALID_HID;  // Initialize to an invalid ID
    hsize_t idx = 0;  // Initialize index to zero

    // Ensure that the input size is sufficient to extract the needed values
    if (size < sizeof(hid_t) + sizeof(hsize_t)) {
        return 0;
    }

    // Extract the hid_t and hsize_t values from the input data
    group_id = *(const hid_t *)data;
    idx = *(const hsize_t *)(data + sizeof(hid_t));

    // Call the function-under-test
    H5G_obj_t obj_type = H5Gget_objtype_by_idx(group_id, idx);

    // Use obj_type in some way, for example, just to avoid compiler warnings
    (void)obj_type;

    return 0;
}