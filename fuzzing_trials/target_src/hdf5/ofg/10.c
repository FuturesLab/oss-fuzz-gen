#include <stdint.h>
#include <stddef.h>
#include <string.h> // Include this for memcpy
#include <hdf5.h>

int LLVMFuzzerTestOneInput_10(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t loc_id1 = H5I_INVALID_HID;
    hid_t loc_id2 = H5I_INVALID_HID;
    char name1[256];
    char name2[256];
    H5L_type_t link_type = H5L_TYPE_HARD;

    // Ensure data size is sufficient for our needs
    if (size < 2) {
        return 0;
    }

    // Initialize HDF5 library
    H5open();

    // Create two HDF5 file identifiers for the purpose of this test
    loc_id1 = H5Fcreate("testfile1.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    loc_id2 = H5Fcreate("testfile2.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Copy data into name1 and name2 ensuring null termination
    size_t name1_len = size / 2 < 255 ? size / 2 : 255;
    size_t name2_len = size - name1_len < 255 ? size - name1_len : 255;
    memcpy(name1, data, name1_len);
    name1[name1_len] = '\0';
    memcpy(name2, data + name1_len, name2_len);
    name2[name2_len] = '\0';

    // Call the function-under-test
    herr_t result = H5Glink2(loc_id1, name1, link_type, loc_id2, name2);

    // Close the HDF5 file identifiers
    if (loc_id1 != H5I_INVALID_HID) {
        H5Fclose(loc_id1);
    }
    if (loc_id2 != H5I_INVALID_HID) {
        H5Fclose(loc_id2);
    }

    // Close the HDF5 library
    H5close();

    return 0;
}