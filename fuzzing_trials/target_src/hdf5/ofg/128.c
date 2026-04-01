#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to extract an hid_t value
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract an hid_t value from the input data
    hid_t file_id = *((hid_t*)data);

    // Call the function-under-test
    hid_t reopened_id = H5Freopen(file_id);

    // Close the reopened file if it was successfully opened
    if (reopened_id >= 0) {
        H5Fclose(reopened_id);
    }

    return 0;
}