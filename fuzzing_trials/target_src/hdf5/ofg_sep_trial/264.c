#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_264(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    hid_t file_id;
    H5F_libver_t low;
    H5F_libver_t high;

    // Ensure the size is sufficient to extract the required parameters
    if (size < 2) {
        return 0;
    }

    // Use the first byte to determine the 'low' version
    low = (H5F_libver_t)(data[0] % (H5F_LIBVER_LATEST + 1));

    // Use the second byte to determine the 'high' version
    high = (H5F_libver_t)(data[1] % (H5F_LIBVER_LATEST + 1));

    // Open a file to obtain a valid hid_t
    file_id = H5Fopen("testfile.h5", H5F_ACC_RDWR, H5P_DEFAULT);
    if (file_id < 0) {
        // If the file cannot be opened, return
        return 0;
    }

    // Call the function-under-test
    herr_t result = H5Fset_libver_bounds(file_id, low, high);

    // Close the file
    H5Fclose(file_id);

    return 0;
}