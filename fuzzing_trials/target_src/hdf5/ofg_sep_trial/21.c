#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t loc_id = H5P_DEFAULT; // Location identifier
    const char *attr_name = "fuzz_attribute"; // Attribute name
    hid_t type_id = H5T_NATIVE_INT; // Data type identifier
    hid_t space_id = H5S_SCALAR; // Dataspace identifier
    hid_t acpl_id = H5P_DEFAULT; // Attribute creation property list identifier
    hid_t aapl_id = H5P_DEFAULT; // Attribute access property list identifier

    // Ensure the data size is sufficient for fuzzing
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Call the function-under-test
    hid_t attr_id = H5Acreate2(loc_id, attr_name, type_id, space_id, acpl_id, aapl_id);

    // Close the attribute if it was successfully created
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }

    return 0;
}