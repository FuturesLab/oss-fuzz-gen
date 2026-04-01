#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_162(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for creating a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Initialize a hid_t variable from the input data
    hid_t file_id = *(const hid_t *)data;

    // Call the function-under-test
    herr_t result = H5Freset_page_buffering_stats(file_id);

    // Use the result in some way to prevent optimization out
    if (result == 0) {
        // Successfully reset page buffering stats
    } else {
        // Handle error if needed
    }

    return 0;
}