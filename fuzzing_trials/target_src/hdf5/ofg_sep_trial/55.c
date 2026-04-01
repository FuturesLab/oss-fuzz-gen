#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_55(const uint8_t *data, size_t size) {
    hid_t dataset_id;
    hid_t datatype_id;

    // Ensure that size is large enough to extract a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t value from the input data
    dataset_id = *(const hid_t *)data;

    // Call the function-under-test
    datatype_id = H5Dget_type(dataset_id);

    // Close the datatype if it's valid
    if (datatype_id >= 0) {
        H5Tclose(datatype_id);
    }

    return 0;
}