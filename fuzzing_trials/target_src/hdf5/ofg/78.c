#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_78(const uint8_t *data, size_t size) {
    // Ensure that size is sufficient to extract a valid hid_t and hsize_t
    if (size < sizeof(hid_t) + sizeof(hsize_t)) {
        return 0;
    }

    // Extract hid_t from the data
    hid_t dataset_id;
    memcpy(&dataset_id, data, sizeof(hid_t));
    data += sizeof(hid_t);
    size -= sizeof(hid_t);

    // Extract hsize_t from the data
    hsize_t dims;
    memcpy(&dims, data, sizeof(hsize_t));

    // Call the function-under-test
    herr_t result = H5Dset_extent(dataset_id, &dims);

    // Use the result variable to avoid unused variable warning
    (void)result;

    return 0;
}