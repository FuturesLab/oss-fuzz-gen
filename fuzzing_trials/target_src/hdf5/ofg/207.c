#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_207(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for creating a valid string
    if (size < 2) return 0;

    // Initialize HDF5 library
    H5open();

    // Create a dummy HDF5 file to work with
    hid_t file_id = H5Fcreate("dummy.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Create a dummy group in the file
    hid_t group_id = H5Gcreate(file_id, "/dummy_group", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (group_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create a dummy attribute in the group
    hid_t space_id = H5Screate(H5S_SCALAR);
    hid_t attr_id = H5Acreate(group_id, "dummy_attr", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT);
    H5Sclose(space_id);
    H5Aclose(attr_id);

    // Prepare the attribute name from input data
    size_t attr_name_len = size - 1;
    char *attr_name = (char *)malloc(attr_name_len + 1);
    memcpy(attr_name, data, attr_name_len);
    attr_name[attr_name_len] = '\0';

    // Call the function-under-test
    hid_t result = H5Aopen_name(group_id, attr_name);

    // Clean up
    free(attr_name);
    if (result >= 0) {
        H5Aclose(result);
    }
    H5Gclose(group_id);
    H5Fclose(file_id);
    H5close();

    return 0;
}