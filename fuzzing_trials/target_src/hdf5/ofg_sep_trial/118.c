#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id;
    haddr_t eoa;

    // Ensure that the size is sufficient for creating a file
    if (size < 1) {
        return 0;
    }

    // Create a new file using the core driver with a unique name
    file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Call the function-under-test
    herr_t status = H5Fget_eoa(file_id, &eoa);

    // Close the file
    H5Fclose(file_id);

    return 0;
}