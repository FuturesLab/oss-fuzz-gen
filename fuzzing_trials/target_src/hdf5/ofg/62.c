#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_62(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t dataset_id;
    H5D_space_status_t space_status;
    herr_t status;

    // Ensure that the input size is sufficient to extract a hid_t value
    if (data == NULL || size < sizeof(hid_t)) {
        return 0;
    }

    // Use the data to create a valid hid_t value
    dataset_id = *((hid_t *)data);

    // Call the function-under-test
    status = H5Dget_space_status(dataset_id, &space_status);

    // Return success
    return 0;
}