#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_261(const uint8_t *data, size_t size) {
    // Initialize variables
    herr_t status;
    hid_t src_loc_id = H5I_INVALID_HID;
    hid_t dst_loc_id = H5I_INVALID_HID;
    const char *src_name = "source_group";
    const char *dst_name = "destination_group";

    // Check if size is sufficient to create a file and groups
    if (size < 1) {
        return 0;
    }

    // Create a new file using default properties.
    hid_t file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a group in the file.
    src_loc_id = H5Gcreate2(file_id, src_name, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (src_loc_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create another group in the file.
    dst_loc_id = H5Gcreate2(file_id, dst_name, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dst_loc_id < 0) {
        H5Gclose(src_loc_id);
        H5Fclose(file_id);
        return 0;
    }

    // Call the function-under-test
    status = H5Gmove2(file_id, src_name, file_id, dst_name);

    // Clean up
    H5Gclose(src_loc_id);
    H5Gclose(dst_loc_id);
    H5Fclose(file_id);

    return 0;
}