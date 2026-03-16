#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_225(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to extract an hid_t value
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract an hid_t value from the input data
    hid_t attribute_id = *((const hid_t *)data);

    // Call the function under test
    hid_t type_id = H5Aget_type(attribute_id);

    // Perform cleanup if necessary
    if (type_id >= 0) {
        H5Tclose(type_id);
    }

    return 0;
}