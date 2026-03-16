#include <stdint.h>
#include <hdf5.h>
#include <stddef.h> // Include for size_t

// Initialize a valid HDF5 attribute for testing
hid_t create_test_attribute() {
    hid_t file_id, space_id, attr_id;
    hsize_t dims[1] = {1};

    // Create a new file using the default properties.
    file_id = H5Fcreate("testfile.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    // Create the data space for the attribute.
    space_id = H5Screate_simple(1, dims, NULL);

    // Create a dataset with a scalar dataspace.
    hid_t dataset_id = H5Dcreate2(file_id, "dataset", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    // Create an attribute for the dataset.
    attr_id = H5Acreate2(dataset_id, "attribute", H5T_NATIVE_INT, space_id, H5P_DEFAULT, H5P_DEFAULT);

    // Close the dataset and the file.
    H5Dclose(dataset_id);
    H5Sclose(space_id);
    H5Fclose(file_id);

    return attr_id;
}

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Use a valid attribute ID for fuzzing
    hid_t attr_id = create_test_attribute();

    // Call the function-under-test
    herr_t result = H5Aclose(attr_id);

    // Normally, you would check the result here, but for fuzzing purposes, we just want to ensure the function is called.
    (void)result;

    return 0;
}