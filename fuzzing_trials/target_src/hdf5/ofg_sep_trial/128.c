#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>  // Include for malloc and free
#include <string.h>  // Include for memcpy
#include <hdf5.h>

int LLVMFuzzerTestOneInput_128(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function parameters
    hid_t dset_id = 1;  // Example dataset identifier, must be valid in real scenarios
    hid_t dxpl_id = 1;  // Example data transfer property list identifier
    hsize_t offset[1] = {0};  // Example offset, assuming 1D dataset
    uint32_t filter_mask = 0;  // Example filter mask
    size_t chunk_size = size < 1024 ? size : 1024;  // Limit chunk size to 1024 bytes
    void *chunk_data = malloc(chunk_size);  // Allocate memory for chunk data
    size_t nbytes;  // Variable to hold the number of bytes read

    if (chunk_data == NULL) {
        return 0;  // Exit if memory allocation fails
    }

    // Copy data into chunk_data
    memcpy(chunk_data, data, chunk_size);

    // Call the function-under-test
    herr_t result = H5Dread_chunk2(dset_id, dxpl_id, offset, &filter_mask, chunk_data, &nbytes);

    // Free allocated memory
    free(chunk_data);

    return 0;
}