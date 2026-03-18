#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_262(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Declare and initialize variables
    hid_t src_loc_id = H5I_INVALID_HID;
    hid_t dst_loc_id = H5I_INVALID_HID;
    char *src_name = NULL;
    char *dst_name = NULL;
    herr_t status;

    // Ensure size is sufficient for two null-terminated strings
    if (size < 4) {
        return 0;
    }

    // Allocate and initialize source and destination names
    size_t half_size = size / 2;
    src_name = (char *)malloc(half_size + 1);
    dst_name = (char *)malloc(half_size + 1);

    if (src_name == NULL || dst_name == NULL) {
        free(src_name);
        free(dst_name);
        return 0;
    }

    memcpy(src_name, data, half_size);
    src_name[half_size] = '\0';

    memcpy(dst_name, data + half_size, half_size);
    dst_name[half_size] = '\0';

    // Create HDF5 file to get valid hid_t identifiers
    hid_t file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id >= 0) {
        src_loc_id = file_id;
        dst_loc_id = file_id;

        // Call the function-under-test
        status = H5Gmove2(src_loc_id, src_name, dst_loc_id, dst_name);

        // Close the file
        H5Fclose(file_id);
    }

    // Free allocated resources
    free(src_name);
    free(dst_name);

    // Close HDF5 library
    H5close();

    return 0;
}