#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_250(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    hid_t loc_id = H5P_DEFAULT;          // Location identifier
    hid_t type_id = H5T_NATIVE_INT;      // Datatype identifier
    hid_t space_id = H5S_SCALAR;         // Dataspace identifier
    hid_t dcpl_id = H5P_DEFAULT;         // Dataset creation property list
    hid_t dapl_id = H5P_DEFAULT;         // Dataset access property list

    // Ensure that the input data is not null and has a minimum size
    if (data == NULL || size < sizeof(int)) {
        return 0;
    }

    // Call the function-under-test
    hid_t dataset_id = H5Dcreate_anon(loc_id, type_id, space_id, dcpl_id, dapl_id);

    // Check if the dataset was created successfully
    if (dataset_id >= 0) {
        // Close the dataset to prevent resource leaks
        H5Dclose(dataset_id);
    }

    return 0;
}