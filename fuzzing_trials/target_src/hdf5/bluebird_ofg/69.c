#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_69(const uint8_t *data, size_t size) {
    hid_t loc_id = H5P_DEFAULT; // Using default property list for location
    const char *attr_name = "fuzz_attribute"; // Attribute name
    hid_t type_id = H5T_NATIVE_INT; // Using native integer type
    hid_t space_id = H5S_SCALAR; // Using scalar dataspace
    hid_t acpl_id = H5P_DEFAULT; // Using default attribute creation property list

    // Ensure that the data is not NULL and has a valid size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Create a copy of the data to use as attribute name if needed
    char *dynamic_attr_name = (char *)malloc(size + 1);
    if (dynamic_attr_name != NULL) {
        memcpy(dynamic_attr_name, data, size);
        dynamic_attr_name[size] = '\0'; // Null-terminate the string
        attr_name = dynamic_attr_name;
    }

    // Call the function-under-test
    hid_t attr_id = H5Acreate1(loc_id, attr_name, type_id, space_id, acpl_id);

    // Clean up
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }
    if (dynamic_attr_name != NULL) {
        free(dynamic_attr_name);
    }

    return 0;
}