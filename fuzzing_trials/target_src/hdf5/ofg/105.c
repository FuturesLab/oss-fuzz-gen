#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating an hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Use the input data to create a hid_t
    hid_t attribute_id = *((hid_t *)data);

    // Call the function-under-test
    herr_t result = H5Aclose(attribute_id);

    // Return 0 to indicate the fuzzer can continue
    return 0;
}