#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_258(const uint8_t *data, size_t size) {
    // Initialize HDF5 library
    H5open();

    // Ensure size is sufficient for two hid_t values
    if (size < 2 * sizeof(hid_t)) {
        return 0;
    }

    // Extract two hid_t values from the input data
    hid_t dataset_id = *((hid_t *)data);
    hid_t fspace_id = *((hid_t *)(data + sizeof(hid_t)));

    // Initialize hsize_t variable for the number of chunks
    hsize_t num_chunks = 0;

    // Call the function-under-test
    herr_t result = H5Dget_num_chunks(dataset_id, fspace_id, &num_chunks);

    // Close HDF5 library
    H5close();

    return 0;
}