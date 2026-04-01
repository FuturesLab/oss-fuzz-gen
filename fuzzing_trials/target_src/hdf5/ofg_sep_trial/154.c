#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_154(const uint8_t *data, size_t size) {
    // Declare and initialize a variable for the file identifier
    hid_t file_id;
    
    // Use a fixed file name for testing purposes
    const char *file_name = "testfile.h5";

    // Create a new HDF5 file using default properties
    file_id = H5Fcreate(file_name, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0; // Return if file creation fails
    }

    // Create a dataspace with a size of the input data
    hsize_t dims[1] = {size};
    hid_t dataspace_id = H5Screate_simple(1, dims, NULL);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0; // Return if dataspace creation fails
    }

    // Create a dataset using the input data
    hid_t dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_UINT8, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0; // Return if dataset creation fails
    }

    // Write the input data to the dataset
    if (H5Dwrite(dataset_id, H5T_NATIVE_UINT8, H5S_ALL, H5S_ALL, H5P_DEFAULT, data) < 0) {
        H5Dclose(dataset_id);
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0; // Return if writing data fails
    }

    // Close the dataset and dataspace
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);

    // Call the function-under-test
    hid_t plist_id = H5Fget_access_plist(file_id);

    // Close the property list if it was successfully retrieved
    if (plist_id >= 0) {
        H5Pclose(plist_id);
    }

    // Close the file
    H5Fclose(file_id);

    return 0;
}