#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an hid_t
    if (size < sizeof(hid_t) || data == NULL) {
        return 0;
    }

    // Extract an hid_t from the input data
    hid_t attribute_id = *((hid_t*)data);

    // Call the function-under-test
    herr_t result = H5Aclose(attribute_id);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}