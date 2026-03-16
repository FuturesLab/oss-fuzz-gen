#include <stdint.h>
#include <stddef.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    hid_t file_id;
    unsigned long fileno;

    // Check if the input size is sufficient for creating a file identifier
    if (size < sizeof(hid_t) || data == NULL) {
        return 0;
    }

    // Use the input data to create a file identifier
    file_id = *((hid_t *)data);

    // Call the function-under-test
    herr_t result = H5Fget_fileno(file_id, &fileno);

    // Return 0 to indicate successful execution of the fuzzer
    return 0;
}