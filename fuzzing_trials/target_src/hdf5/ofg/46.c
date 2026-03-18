#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_46(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    hid_t loc_id = H5Fopen("testfile.h5", H5F_ACC_RDONLY, H5P_DEFAULT);
    hid_t aapl_id = H5P_DEFAULT;

    // Ensure there is data to use for the attribute name
    if (size == 0 || loc_id < 0) {
        if (loc_id >= 0) {
            H5Fclose(loc_id);
        }
        return 0;
    }

    // Create a null-terminated string for the attribute name
    char attr_name[size + 1];
    for (size_t i = 0; i < size; i++) {
        attr_name[i] = data[i];
    }
    attr_name[size] = '\0';

    // Call the function-under-test
    hid_t attr_id = H5Aopen(loc_id, attr_name, aapl_id);

    // Clean up
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }
    if (loc_id >= 0) {
        H5Fclose(loc_id);
    }

    return 0;
}