#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_195(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id = -1;
    hid_t group_id = -1;
    hsize_t idx = 0;
    H5G_obj_t obj_type;

    // Check if size is sufficient to extract meaningful data for idx
    if (size < sizeof(hsize_t)) {
        return 0;
    }

    // Initialize HDF5 library
    H5open();

    // Create a new HDF5 file
    file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) goto cleanup;

    // Create a group in the file
    group_id = H5Gcreate2(file_id, "/fuzz_group", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (group_id < 0) goto cleanup;

    // Use data to determine the index
    idx = *((hsize_t*)data);

    // Call the function-under-test
    obj_type = H5Gget_objtype_by_idx(group_id, idx);

cleanup:
    // Close the group and file
    if (group_id >= 0) H5Gclose(group_id);
    if (file_id >= 0) H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}