#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>
#include <H5Gpublic.h>

int LLVMFuzzerTestOneInput_11(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient for the test
    if (size < 1) {
        return 0;
    }

    // Initialize the HDF5 library
    H5open();

    // Create a file to use for testing
    hid_t file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a group in the file
    hid_t group_id = H5Gcreate2(file_id, "/test_group", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (group_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Prepare parameters for H5Gget_objinfo
    const char *name = "/test_group";
    bool follow_link = (data[0] % 2 == 0); // Use the first byte to determine the boolean value
    H5G_stat_t statbuf;

    // Call the function-under-test
    herr_t status = H5Gget_objinfo(file_id, name, follow_link, &statbuf);

    // Cleanup
    H5Gclose(group_id);
    H5Fclose(file_id);
    H5close();

    return 0;
}