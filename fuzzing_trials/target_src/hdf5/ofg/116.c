#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for a hid_t type
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t from the input data
    hid_t dataset_id = *(hid_t *)data;

    // Call the function-under-test
    hid_t dataspace_id = H5Dget_space(dataset_id);

    // Normally, you would do some checks or further operations with dataspace_id
    // For fuzzing, we just need to ensure the function is called

    // Close the dataspace_id if it's valid
    if (dataspace_id >= 0) {
        H5Sclose(dataspace_id);
    }

    return 0;
}