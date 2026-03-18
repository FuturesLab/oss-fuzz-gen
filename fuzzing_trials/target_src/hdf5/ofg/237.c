#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_237(const uint8_t *data, size_t size) {
    // Declare and initialize variables for the function-under-test
    hid_t dataset_id = 1; // Assuming a valid dataset ID for testing purposes
    hsize_t coord[2] = {1, 1}; // Example coordinates, assuming a 2D dataset
    unsigned int filter_mask = 0;
    haddr_t addr = 0;
    hsize_t size_out = 0;

    // Call the function-under-test
    herr_t result = H5Dget_chunk_info_by_coord(dataset_id, coord, &filter_mask, &addr, &size_out);

    // Use the result in some way to avoid compiler optimizations
    if (result < 0) {
        // Handle error if needed
    }

    return 0;
}