#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_214(const uint8_t *data, size_t size) {
    // Ensure that the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Convert the input data to a null-terminated string
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        return 0;
    }
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Use a valid file access property list identifier
    hid_t fapl_id = H5P_DEFAULT;

    // Call the function-under-test
    htri_t result = H5Fis_accessible(filename, fapl_id);

    // Clean up
    free(filename);

    return 0;
}