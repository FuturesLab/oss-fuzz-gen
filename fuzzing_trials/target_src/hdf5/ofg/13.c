#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    hid_t loc_id;
    char *name;

    // Ensure size is enough to extract meaningful data
    if (size < sizeof(hid_t) + 1) {
        return 0;
    }

    // Extract hid_t from the input data
    loc_id = *((hid_t *)data);

    // Allocate memory for the name string and ensure it is null-terminated
    name = (char *)malloc(size - sizeof(hid_t) + 1);
    if (name == NULL) {
        return 0;
    }
    memcpy(name, data + sizeof(hid_t), size - sizeof(hid_t));
    name[size - sizeof(hid_t)] = '\0';

    // Call the function-under-test
    H5Funmount(loc_id, name);

    // Clean up
    free(name);

    return 0;
}