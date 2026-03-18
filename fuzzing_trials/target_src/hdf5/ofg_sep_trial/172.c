#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
    // Ensure that the input data is large enough to be used as a file name.
    if (size < 5) {
        return 0;
    }

    // Create a null-terminated string for the file name.
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        return 0;
    }
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Use a valid hid_t value. H5P_DEFAULT is a commonly used default value.
    hid_t fapl_id = H5P_DEFAULT;

    // Call the function-under-test.
    herr_t result = H5Fdelete(filename, fapl_id);

    // Clean up.
    free(filename);

    return 0;
}