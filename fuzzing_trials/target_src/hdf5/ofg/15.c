#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_15(const uint8_t *data, size_t size) {
    hid_t file_id;
    hid_t dataset_id;
    hid_t dataspace_id;
    hsize_t dims[1] = {10}; // Example dimension size
    herr_t status;
    int num_attrs;

    // Initialize HDF5 library
    H5open();

    // Create a new file using the default properties.
    file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Create the data space for the dataset.
    dataspace_id = H5Screate_simple(1, dims, NULL);

    // Create a dataset in the file.
    dataset_id = H5Dcreate2(file_id, "dset", H5T_NATIVE_INT, dataspace_id, 
                            H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Call the function-under-test
    num_attrs = H5Aget_num_attrs(dataset_id);

    // Clean up
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}