#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_182(const uint8_t *data, size_t size) {
    // Ensure size is sufficient for creating a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Create a hid_t from the input data
    hid_t dataset_id = *(const hid_t *)data;

    // Initialize H5D_chunk_index_t variable
    H5D_chunk_index_t index_type;

    // Call the function-under-test
    herr_t result = H5Dget_chunk_index_type(dataset_id, &index_type);

    // Use the result in some way to avoid compiler optimizations
    if (result < 0) {
        // Handle error (for fuzzing, we simply return)
        return 0;
    }

    // Further processing can be done here if needed

    return 0;
}