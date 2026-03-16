#include <stdint.h>
#include <hdf5.h>
#include <H5Dpublic.h>

int LLVMFuzzerTestOneInput_182(const uint8_t *data, size_t size) {
    // Initialize variables
    hid_t dataset_id = H5I_INVALID_HID;
    H5D_chunk_index_t chunk_index_type;

    // Ensure that size is sufficient for a valid dataset identifier
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a valid dataset identifier from the input data
    dataset_id = *((hid_t *)data);

    // Call the function-under-test
    herr_t result = H5Dget_chunk_index_type(dataset_id, &chunk_index_type);

    // The result and chunk_index_type can be used for further validation if needed

    return 0;
}