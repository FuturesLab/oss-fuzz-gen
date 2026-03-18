#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a hid_t value
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t value from the input data
    hid_t dataset_id = *(const hid_t *)data;

    // Call the function-under-test
    hid_t dataspace_id = H5Dget_space(dataset_id);

    // Perform any necessary cleanup
    if (dataspace_id >= 0) {
        H5Sclose(dataspace_id);
    }

    return 0;
}