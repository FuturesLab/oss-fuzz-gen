#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_224(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t attribute_id = H5I_INVALID_HID; // Invalid ID to start with
    H5A_info_t ainfo;

    // Ensure that the size is sufficient to create a valid attribute
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Create a temporary file and dataset to obtain a valid attribute ID
    hid_t file_id = H5Fcreate("tempfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    if (file_id < 0) {
        return 0;
    }

    hid_t dataspace_id = H5Screate(H5S_SCALAR);
    if (dataspace_id < 0) {
        H5Fclose(file_id);
        return 0;
    }

    hid_t dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (dataset_id < 0) {
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Create an attribute to get a valid attribute ID
    attribute_id = H5Acreate2(dataset_id, "attribute", H5T_NATIVE_INT, dataspace_id, H5P_DEFAULT, H5P_DEFAULT);
    if (attribute_id < 0) {
        H5Dclose(dataset_id);
        H5Sclose(dataspace_id);
        H5Fclose(file_id);
        return 0;
    }

    // Call the function-under-test
    herr_t status = H5Aget_info(attribute_id, &ainfo);

    // Clean up resources
    H5Aclose(attribute_id);
    H5Dclose(dataset_id);
    H5Sclose(dataspace_id);
    H5Fclose(file_id);

    return 0;
}