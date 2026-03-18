#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_225(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t attribute_id;
    hid_t datatype_id;

    // Ensure size is sufficient for a valid hid_t input
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Copy data to hid_t variable
    attribute_id = *(const hid_t *)data;

    // Call the function-under-test
    datatype_id = H5Aget_type(attribute_id);

    // Close the datatype if it is valid
    if (datatype_id >= 0) {
        H5Tclose(datatype_id);
    }

    return 0;
}