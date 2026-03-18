#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    hid_t loc_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (loc_id < 0) {
        return 0; // Unable to create file, exit early
    }

    // Ensure the data is null-terminated for use as a string
    char attr_name[256];
    size_t copy_size = (size < 255) ? size : 255;
    memcpy(attr_name, data, copy_size);
    attr_name[copy_size] = '\0';

    hid_t aapl_id = H5Pcreate(H5P_ATTRIBUTE_ACCESS);
    if (aapl_id < 0) {
        H5Fclose(loc_id);
        return 0; // Unable to create property list, exit early
    }

    // Call the function-under-test
    hid_t attr_id = H5Aopen(loc_id, attr_name, aapl_id);

    // Clean up resources
    if (attr_id >= 0) {
        H5Aclose(attr_id);
    }
    H5Pclose(aapl_id);
    H5Fclose(loc_id);

    return 0;
}