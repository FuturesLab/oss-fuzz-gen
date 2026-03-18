#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id = -1;
    hid_t reopened_file_id;

    // Ensure that there is enough data to create a valid file name
    if (size < 5) {
        return 0;
    }

    // Create a unique file name using the provided data
    char filename[6];
    for (int i = 0; i < 5; i++) {
        filename[i] = (char)(data[i] % 26 + 'A'); // Convert to a valid character
    }
    filename[5] = '\0';

    // Create a new HDF5 file using the generated filename
    file_id = H5Fcreate(filename, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Call the function-under-test
    reopened_file_id = H5Freopen(file_id);

    // Close the files if they were successfully opened
    if (reopened_file_id >= 0) {
        H5Fclose(reopened_file_id);
    }
    if (file_id >= 0) {
        H5Fclose(file_id);
    }

    return 0;
}