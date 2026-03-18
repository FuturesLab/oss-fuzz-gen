#include <stdint.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_63(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t dataset_id = H5I_INVALID_HID;  // Invalid ID for initialization
    H5D_space_status_t space_status = H5D_SPACE_STATUS_NOT_ALLOCATED;  // Initialize with a valid enum value

    // Check if the size is sufficient to extract an hid_t value
    if (size >= sizeof(hid_t)) {
        // Extract hid_t from the input data
        dataset_id = *(const hid_t *)data;
    }

    // Call the function-under-test
    herr_t result = H5Dget_space_status(dataset_id, &space_status);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}