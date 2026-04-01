#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_58(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Create a file to work with
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Create a dummy dataset to ensure the dataset exists for opening
    hsize_t dims[1] = {10};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
    hid_t dataset_id = H5Dcreate2(file_id, "dset", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Close the dataset and dataspace
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);

    // Prepare the input parameters for H5Dopen2
    hid_t loc_id = file_id;
    const char *name = "dset";
    hid_t dapl_id = H5P_DEFAULT;

    // Call the function-under-test
    hid_t result = H5Dopen2(loc_id, name, dapl_id);

    // Close the dataset if it was successfully opened
    if (result >= 0) {
        H5Dclose(result);
    }

    // Close the file
    H5Fclose(file_id);

    // Close the HDF5 library
    H5close();

    return 0;
}