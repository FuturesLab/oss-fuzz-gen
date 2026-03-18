#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_206(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a valid string
    if (size < 1) {
        return 0;
    }

    // Create a valid HDF5 file in memory
    hid_t file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    // Create a dataset in the file
    hid_t dataspace_id = H5Screate(H5S_SCALAR);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t dataset_id = H5Dcreate(file_id, "dataset", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Create an attribute for the dataset
    hid_t attr_id = H5Acreate(dataset_id, "attribute", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attr_id < 0) {
        H5Dclose(dataset_id);
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Close the attribute
    H5Aclose(attr_id);

    // Use the data as a name for H5Aopen_name
    char name[256];
    size_t name_length = size < 255 ? size : 255;
    memcpy(name, data, name_length);
    name[name_length] = '\0';

    // Call the function under test
    hid_t result = H5Aopen_name(dataset_id, name);

    // Clean up
    if (result >= 0) {
        H5Aclose(result);
    }
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    return 0;
}