#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>
#include <H5Dpublic.h>

int LLVMFuzzerTestOneInput_181(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t dataset_id;
    H5D_chunk_index_t chunk_index_type;
    herr_t status;

    // Ensure that the input data is large enough to extract a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Use the first bytes of data to create a hid_t value
    dataset_id = *((hid_t*)data);

    // Call the function-under-test
    status = H5Dget_chunk_index_type(dataset_id, &chunk_index_type);

    // Optionally, handle the status or chunk_index_type if needed

    return 0;
}