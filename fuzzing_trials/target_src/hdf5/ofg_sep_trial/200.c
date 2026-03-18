#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_200(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t dataset_id;
    hsize_t chunk_dims[2] = {1, 1}; // Assuming a 2D chunk for simplicity
    hsize_t storage_size;

    // Ensure data size is sufficient for hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract dataset_id from input data
    dataset_id = *(const hid_t *)data;
    
    // Call the function-under-test
    herr_t result = H5Dget_chunk_storage_size(dataset_id, chunk_dims, &storage_size);

    // Use the result and storage_size in some way to avoid compiler optimizations
    (void)result;
    (void)storage_size;

    return 0;
}