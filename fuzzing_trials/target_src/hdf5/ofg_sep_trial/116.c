#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_116(const uint8_t *data, size_t size) {
    hid_t dataset_id;
    hid_t dataspace_id;

    // Ensure we have enough data to form a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Cast the first part of data to hid_t
    dataset_id = *(const hid_t *)data;

    // Call the function-under-test
    dataspace_id = H5Dget_space(dataset_id);

    // Normally, you would check the dataspace_id here and perform further operations
    // For fuzzing, we just ensure that the function is called

    // If dataspace_id is valid, close it
    if (dataspace_id >= 0) {
        H5Sclose(dataspace_id);
    }

    return 0;
}