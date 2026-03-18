#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

extern int LLVMFuzzerTestOneInput_5(const uint8_t *data, size_t size) {
    hid_t file_id, dataset_id, dataspace_id;
    hsize_t dims[1] = {size}; // Use the size of the input data as the dimension

    // Initialize HDF5 library
    H5open();

    // Create a new file using default properties.
    file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Ensure the file_id is valid
    if (file_id < 0) {
        return 0;
    }

    // Create a dataspace for the dataset
    dataspace_id = H5Screate_simple(1, dims, NULL);

    // Create the dataset with the input data
    dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_UINT8, dataspace_id, 
                            H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Write the input data to the dataset
    if (dataset_id >= 0) {
        H5Dwrite(dataset_id, H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);
        H5Dclose(dataset_id);
    }

    // Close the dataspace
    H5Sclose(dataspace_id);

    // Close the file
    H5Fclose(file_id);

    // Terminate access to the HDF5 library
    H5close();

    return 0;
}