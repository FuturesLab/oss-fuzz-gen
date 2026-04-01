#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_70(const uint8_t *data, size_t size) {
    if (size < 1) return 0;

    // Initialize HDF5 library
    H5open();

    // Create a temporary file to work with
    hid_t file_id = H5Fcreate("temp_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) return 0;

    // Create a dummy dataset
    hid_t space_id = H5Screate(H5S_SCALAR);
    hid_t dset_id = H5Dcreate(file_id, "dummy_dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Create an attribute for the dataset
    hid_t attr_id = H5Acreate(dset_id, "dummy_attribute", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT);

    if (attr_id < 0) {
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Close the attribute
    H5Aclose(attr_id);

    // Use the input data to create a null-terminated string for the attribute name
    char attr_name[256];
    size_t attr_name_len = size < 255 ? size : 255;
    for (size_t i = 0; i < attr_name_len; i++) {
        attr_name[i] = (char)data[i];
    }
    attr_name[attr_name_len] = '\0';

    // Call the function-under-test
    H5Adelete(dset_id, attr_name);

    // Clean up
    H5Dclose(dset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}