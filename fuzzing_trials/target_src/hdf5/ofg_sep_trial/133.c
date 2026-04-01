#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_133(const uint8_t *data, size_t size) {
    // Initialize variables for the H5Dcreate2 function call
    hid_t loc_id = H5P_DEFAULT;  // Default location identifier
    const char *name = "dataset";  // Name of the dataset
    hid_t type_id = H5T_NATIVE_INT;  // Default datatype identifier
    hid_t space_id = H5S_SIMPLE;  // Default dataspace identifier
    hid_t lcpl_id = H5P_DEFAULT;  // Default link creation property list
    hid_t dcpl_id = H5P_DEFAULT;  // Default dataset creation property list
    hid_t dapl_id = H5P_DEFAULT;  // Default dataset access property list

    // Create a dataspace for the dataset
    hsize_t dims[1] = {10};  // Example dimension size
    space_id = H5Screate_simple(1, dims, NULL);

    // Call the function-under-test
    hid_t dataset_id = H5Dcreate2(loc_id, name, type_id, space_id, lcpl_id, dcpl_id, dapl_id);

    // Close the dataspace and dataset if they were successfully created
    if (dataset_id >= 0) {
        H5Dclose(dataset_id);
    }
    if (space_id >= 0) {
        H5Sclose(space_id);
    }

    return 0;
}