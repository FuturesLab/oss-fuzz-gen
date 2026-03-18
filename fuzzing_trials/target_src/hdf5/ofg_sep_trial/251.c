#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_251(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    hid_t loc_id = H5P_DEFAULT;  // Use default property list
    hid_t type_id = H5T_NATIVE_INT;  // Use native integer type
    hid_t space_id = H5Screate(H5S_SCALAR);  // Create a scalar dataspace
    hid_t dcpl_id = H5Pcreate(H5P_DATASET_CREATE);  // Create dataset creation property list
    hid_t dapl_id = H5P_DEFAULT;  // Use default access property list

    // Call the function-under-test
    hid_t dataset_id = H5Dcreate_anon(loc_id, type_id, space_id, dcpl_id, dapl_id);

    // Check if dataset creation was successful
    if (dataset_id >= 0) {
        // Close the dataset to prevent resource leaks
        H5Dclose(dataset_id);
    }

    // Clean up resources
    H5Sclose(space_id);
    H5Pclose(dcpl_id);

    return 0;
}