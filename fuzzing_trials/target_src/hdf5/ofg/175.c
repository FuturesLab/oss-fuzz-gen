#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_175(const uint8_t *data, size_t size) {
    hid_t loc_id = 1; // Assuming a valid location identifier
    const char *obj_name = "example_object";
    const char *attr_name = "example_attribute";
    H5A_info_t ainfo;
    hid_t lapl_id = H5P_DEFAULT; // Default link access property list

    // Call the function-under-test
    herr_t result = H5Aget_info_by_name(loc_id, obj_name, attr_name, &ainfo, lapl_id);

    // Use the result in some way to avoid compiler optimizations removing the call
    if (result < 0) {
        // Handle error case
    }

    return 0;
}