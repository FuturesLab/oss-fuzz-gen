#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_173(const uint8_t *data, size_t size) {
    // Ensure that the data size is sufficient for creating a valid string
    if (size < 1) {
        return 0;
    }

    // Allocate memory for the file name and ensure it's null-terminated
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        return 0;
    }
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Initialize a non-null hid_t value
    hid_t fapl_id = H5P_DEFAULT;

    // Call the function under test
    H5Fdelete(filename, fapl_id);

    // Clean up
    free(filename);

    return 0;
}