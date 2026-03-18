#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_123(const uint8_t *data, size_t size) {
    // Ensure the data size is large enough to create a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a hid_t from the input data
    hid_t dataset_id = *(const hid_t *)data;

    // Call the function-under-test
    hsize_t storage_size = H5Dget_storage_size(dataset_id);

    // Use the storage_size in some way to prevent optimization out
    volatile hsize_t use_storage_size = storage_size;
    (void)use_storage_size;

    return 0;
}