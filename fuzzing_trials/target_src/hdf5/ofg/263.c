#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_263(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    hid_t file_id;
    H5F_libver_t low_bound, high_bound;

    // Ensure the input size is sufficient to extract needed values
    if (size < 3) {
        return 0;
    }

    // Use the input data to set the bounds, ensuring they are within valid range
    low_bound = (H5F_libver_t)(data[0] % (H5F_LIBVER_LATEST + 1));
    high_bound = (H5F_libver_t)(data[1] % (H5F_LIBVER_LATEST + 1));

    // Create a new HDF5 file to get a valid file_id
    file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    herr_t status = H5Fset_libver_bounds(file_id, low_bound, high_bound);

    // Close the file
    H5Fclose(file_id);

    return 0;
}