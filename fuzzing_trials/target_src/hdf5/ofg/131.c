#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    // Initialize variables for the function call
    hid_t loc_id = 1; // Example non-null identifier
    const char *name = "dataset"; // Example dataset name
    hid_t type_id = 2; // Example non-null identifier
    hid_t space_id = 3; // Example non-null identifier
    hid_t lcpl_id = H5P_DEFAULT; // Use default link creation property list
    hid_t dcpl_id = H5P_DEFAULT; // Use default dataset creation property list
    hid_t dapl_id = H5P_DEFAULT; // Use default dataset access property list

    // Call the function-under-test
    hid_t dataset_id = H5Dcreate2(loc_id, name, type_id, space_id, lcpl_id, dcpl_id, dapl_id);

    // Close the dataset if it was successfully created
    if (dataset_id >= 0) {
        H5Dclose(dataset_id);
    }

    return 0;
}