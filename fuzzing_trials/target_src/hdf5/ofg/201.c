#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_201(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t dataset_id = H5I_INVALID_HID; // Invalid ID for initialization
    hsize_t dims[2] = {1, 1}; // Example dimensions, not NULL
    hsize_t storage_size = 0; // Variable to store the chunk storage size

    // Ensure the input size is sufficient for our needs
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Use the input data to set the dataset_id
    dataset_id = *(hid_t *)data;

    // Call the function-under-test
    herr_t result = H5Dget_chunk_storage_size(dataset_id, dims, &storage_size);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}