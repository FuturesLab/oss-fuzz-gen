#include <stdint.h>
#include <hdf5.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    // Ensure that the size is sufficient to create a valid hid_t
    if (size < sizeof(hid_t)) {
        return 0;
    }

    // Extract a potential hid_t from the input data
    hid_t attribute_id = *(const hid_t *)data;

    // Call the function-under-test
    hsize_t storage_size = H5Aget_storage_size(attribute_id);

    // Optionally print the storage size for debugging
    printf("Storage size: %llu\n", (unsigned long long)storage_size);

    return 0;
}