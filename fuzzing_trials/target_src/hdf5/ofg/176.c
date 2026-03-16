#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_176(const uint8_t *data, size_t size) {
    hid_t loc_id = H5I_INVALID_HID;
    hid_t lapl_id = H5P_DEFAULT;
    H5A_info_t ainfo;

    // Ensure data is not empty and has enough size for null-terminated strings
    if (size < 2) {
        return 0;
    }

    // Use the data to create strings for `obj_name` and `attr_name`
    size_t obj_name_len = data[0] % size;
    size_t attr_name_len = (data[1] % (size - obj_name_len)) + 1;

    char obj_name[obj_name_len + 1];
    char attr_name[attr_name_len + 1];

    if (obj_name_len + attr_name_len + 2 > size) {
        return 0;
    }

    // Copy data into strings and null-terminate them
    for (size_t i = 0; i < obj_name_len; i++) {
        obj_name[i] = data[i + 2];
    }
    obj_name[obj_name_len] = '\0';

    for (size_t i = 0; i < attr_name_len; i++) {
        attr_name[i] = data[i + 2 + obj_name_len];
    }
    attr_name[attr_name_len] = '\0';

    // Fuzz the function-under-test
    H5Aget_info_by_name(loc_id, obj_name, attr_name, &ainfo, lapl_id);

    return 0;
}