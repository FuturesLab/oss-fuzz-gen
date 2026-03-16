#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_120(const uint8_t *data, size_t size) {
    // Initialize variables for H5Dwrite_chunk
    hid_t dset_id = 1; // Assuming a valid dataset ID
    hid_t dxpl_id = H5P_DEFAULT; // Default data transfer property list
    uint32_t filters = 0; // No filters applied
    hsize_t offset[1] = {0}; // Offset for the chunk
    size_t chunk_size = size > 0 ? size : 1; // Ensure size is not zero
    const void *buf = (const void *)data; // Data buffer

    // Call the function-under-test
    herr_t result = H5Dwrite_chunk(dset_id, dxpl_id, filters, offset, chunk_size, buf);

    return 0;
}