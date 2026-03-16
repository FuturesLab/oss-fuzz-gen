#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_114(const uint8_t *data, size_t size) {
    // Initialize variables for the function call
    hid_t loc_id = H5P_DEFAULT; // Using default property list
    const char *obj_name = "example_object";
    const char *attr_name = "example_attribute";
    hid_t aapl_id = H5P_DEFAULT; // Using default attribute access property list
    hid_t lapl_id = H5P_DEFAULT; // Using default link access property list

    // Ensure the data is not empty before using it
    if (size > 0) {
        // Call the function-under-test
        hid_t attr_id = H5Aopen_by_name(loc_id, obj_name, attr_name, aapl_id, lapl_id);

        // Close the attribute if it was successfully opened
        if (attr_id >= 0) {
            H5Aclose(attr_id);
        }
    }

    return 0;
}