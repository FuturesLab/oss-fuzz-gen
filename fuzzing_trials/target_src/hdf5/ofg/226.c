#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_226(const uint8_t *data, size_t size) {
    // Ensure the data size is large enough to extract a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract hid_t from the input data
    hid_t attribute_id = *(const hid_t *)data;

    // Call the function-under-test
    hid_t type_id = H5Aget_type(attribute_id);

    // Close the type_id if it's valid to avoid resource leaks
    if (type_id >= 0) {
        H5Tclose(type_id);
    }

    return 0;
}