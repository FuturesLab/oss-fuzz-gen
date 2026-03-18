#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_167(const uint8_t *data, size_t size) {
    // Initialize the HDF5 library
    H5open();

    // Create a file in memory using the data as the file contents
    hid_t fapl_id = H5Pcreate(H5P_FILE_ACCESS);
    H5Pset_fapl_core(fapl_id, (size_t)1024, 0);

    hid_t file_id = H5Fcreate("fuzz_test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, fapl_id);

    // Create a simple dataspace
    hsize_t dims[1] = {10};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);

    // Create a dataset
    hid_t dataset_id = H5Dcreate2(file_id, "dset", H5T_NATIVE_INT, dataspace_id,
                                  H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Call the function-under-test
    herr_t status = H5Dformat_convert(dataset_id);

    // Close the dataset and file
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);
    H5Pclose(fapl_id);

    // Terminate the HDF5 library
    H5close();

    return 0;
}