#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_204(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t loc_id = H5P_DEFAULT;  // Use default property list for location
    hid_t type_id = H5T_NATIVE_INT;  // Use native integer type
    hid_t space_id = H5S_SCALAR;  // Use scalar dataspace
    hid_t acpl_id = H5P_DEFAULT;  // Use default attribute creation property list

    // Ensure that the provided data is non-empty and null-terminated for the attribute name
    if (size == 0) return 0;

    char *attr_name = (char *)malloc(size + 1);
    if (attr_name == NULL) return 0;

    memcpy(attr_name, data, size);
    attr_name[size] = '\0';  // Null-terminate the string

    // Call the function-under-test
    hid_t attr_id = H5Acreate1(loc_id, attr_name, type_id, space_id, acpl_id);

    // Clean up
    free(attr_name);

    // Close the attribute if it was successfully created
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }

    return 0;
}