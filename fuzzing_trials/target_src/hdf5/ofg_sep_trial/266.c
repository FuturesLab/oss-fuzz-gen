#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_266(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t group_id = H5I_INVALID_HID;  // Invalid ID to start with
    hsize_t idx = 0;
    char obj_name[256];  // Buffer to store the object name
    size_t buf_size = sizeof(obj_name);

    // Ensure size is sufficient to extract meaningful data
    if (size < sizeof(hid_t) + sizeof(hsize_t)) {
        return 0;
    }

    // Extract hid_t and hsize_t from the input data
    memcpy(&group_id, data, sizeof(hid_t));
    memcpy(&idx, data + sizeof(hid_t), sizeof(hsize_t));

    // Call the function under test
    ssize_t result = H5Gget_objname_by_idx(group_id, idx, obj_name, buf_size);

    // Use the result to prevent compiler optimizations removing the call
    if (result >= 0) {
        obj_name[result] = '\0';  // Null-terminate if successful
    }

    return 0;
}