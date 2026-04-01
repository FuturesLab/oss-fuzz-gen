#include <stdint.h>
#include <stddef.h>
#include <string.h>  // Include for memcpy function
#include <hdf5.h>

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    hid_t file_id;
    herr_t status;
    char mount_name[256];

    // Ensure size is sufficient for mount_name
    if (size < 1) {
        return 0;
    }

    // Initialize the HDF5 library
    H5open();

    // Create a new file using default properties.
    file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Copy data to mount_name ensuring null termination
    size_t copy_size = size < sizeof(mount_name) - 1 ? size : sizeof(mount_name) - 1;
    memcpy(mount_name, data, copy_size);
    mount_name[copy_size] = '\0';

    // Call the function-under-test
    status = H5Funmount(file_id, mount_name);

    // Close the file
    H5Fclose(file_id);

    // Close the HDF5 library
    H5close();

    return 0;
}