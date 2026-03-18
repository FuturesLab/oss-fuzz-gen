#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient for our needs
    if (size < 10) {
        return 0;
    }

    // Initialize HDF5 library
    H5open();

    // Create a file to work with
    hid_t file_id = H5Fcreate("fuzz_test_file.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a dataspace
    hsize_t dims[1] = {10};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    // Use part of the data as a dataset name
    char dataset_name[5];
    for (int i = 0; i < 4; ++i) {
        dataset_name[i] = (char)data[i];
    }
    dataset_name[4] = '\0';

    // Use part of the data to create a datatype
    hid_t datatype_id = H5Tcopy(H5T_NATIVE_INT);
    if (datatype_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Use part of the data to create a dataset creation property list
    hid_t dcpl_id = H5Pcreate(H5P_DATASET_CREATE);
    if (dcpl_id < 0) {
        H5Tclose(datatype_id);
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Call the function-under-test
    hid_t dataset_id = H5Dcreate2(file_id, dataset_name, datatype_id, dataspace_id, H5P_DEFAULT, dcpl_id, H5P_DEFAULT);

    // Clean up
    if (dataset_id >= 0) {
        H5Dclose(dataset_id);
    }
    H5Pclose(dcpl_id);
    H5Tclose(datatype_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    // Close HDF5 library
    H5close();

    return 0;
}