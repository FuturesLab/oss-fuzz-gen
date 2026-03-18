#include <stdint.h>
#include <stdlib.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_152(const uint8_t *data, size_t size) {
    // Initialize variables for the function parameters
    hid_t attr_id = H5I_INVALID_HID;
    hid_t mem_type_id = H5T_NATIVE_INT;
    void *buf = malloc(sizeof(int)); // Allocate memory for buffer
    hid_t es_id = H5I_INVALID_HID;

    // Ensure buf is not NULL
    if (buf == NULL) {
        return 0;
    }

    // Initialize the buffer with some data
    if (size >= sizeof(int)) {
        *((int *)buf) = *((const int *)data);
    } else {
        *((int *)buf) = 0;
    }

    // Call the function-under-test
    herr_t result = H5Awrite_async(attr_id, mem_type_id, buf, es_id);

    // Free allocated memory
    free(buf);

    return 0;
}