#include <stdint.h>
#include <hdf5.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_223(const uint8_t *data, size_t size) {
    // Ensure that we have enough data to work with
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t value from the input data
    hid_t input_id = *((hid_t *)data);

    // Initialize the H5A_info_t structure
    H5A_info_t attr_info;

    // Call the function-under-test
    herr_t result = H5Aget_info(input_id, &attr_info);

    // Use the result and attr_info for further processing if needed
    // (In a real fuzzing scenario, you might want to check the result
    // and perform additional operations based on it)

    return 0;
}