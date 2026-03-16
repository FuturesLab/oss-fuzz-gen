#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_18(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a memory file to avoid file I/O
    hid_t file_id = H5Fcreate("tempfile", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a dataspace
    hsize_t dims[1] = {10};
    hid_t space_id = H5Screate_simple(1, dims, NULL);
    if (space_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Create a dataset
    hid_t dset_id = H5Dcreate(file_id, "dset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dset_id < 0) {
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Create an attribute
    hid_t attr_id = H5Acreate(dset_id, "attr", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id < 0) {
        H5Dclose(dset_id);
        H5Sclose(space_id);
        H5Fclose(file_id);
        return 0;
    }

    // Close the attribute, dataspace, and dataset
    H5Aclose(attr_id);
    H5Sclose(space_id);
    H5Dclose(dset_id);

    // Fuzz the function H5Aget_num_attrs
    int num_attrs = H5Aget_num_attrs(file_id);

    // Cleanup
    H5Fclose(file_id);
    H5close();

    return 0;
}