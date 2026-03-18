#include <stdint.h>
#include <stdbool.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_141(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t file_id;
    bool no_attrs_hint;

    // Ensure size is sufficient for our needs
    if (size < sizeof(bool)) {
        return 0;
    }

    // Create a new HDF5 file to get a valid file identifier
    file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Unable to create file, exit early
    }

    // Extract a boolean value from the input data
    no_attrs_hint = data[0] % 2 == 0; // Use the first byte to determine the boolean value

    // Call the function-under-test
    herr_t result = H5Fset_dset_no_attrs_hint(file_id, no_attrs_hint);

    // Close the HDF5 file
    H5Fclose(file_id);

    return 0;
}