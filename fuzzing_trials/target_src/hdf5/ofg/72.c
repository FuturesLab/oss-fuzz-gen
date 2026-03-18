#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_72(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a hid_t value
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t value from the input data
    hid_t attribute_id = *(const hid_t *)data;

    // Call the function-under-test
    hid_t dataspace_id = H5Aget_space(attribute_id);

    // Normally, you would check the dataspace_id for validity and perform
    // additional operations, but for fuzzing, we are only interested in
    // executing the function to check for memory corruption.

    // Close the dataspace if it was successfully created
    if (dataspace_id >= 0) {
        H5Sclose(dataspace_id);
    }

    return 0;
}