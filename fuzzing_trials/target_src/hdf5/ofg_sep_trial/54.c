#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t from the input data
    hid_t dataset_id = *(const hid_t *)data;

    // Call the function-under-test
    hid_t datatype_id = H5Dget_type(dataset_id);

    // Check if the datatype_id is valid and close it
    if (datatype_id >= 0) {
        H5Tclose(datatype_id);
    }

    return 0;
}