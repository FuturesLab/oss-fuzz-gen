#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_213(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for a null-terminated string
    if (size < 2) {
        return 0;
    }

    // Allocate memory for the file name string
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        return 0;
    }

    // Copy data into filename and null-terminate it
    memcpy(filename, data, size);
    filename[size] = '\0';

    // Use a valid hid_t for fapl_id, H5P_DEFAULT is often used for default property lists
    hid_t fapl_id = H5P_DEFAULT;

    // Call the function-under-test
    htri_t result = H5Fis_accessible(filename, fapl_id);

    // Free allocated memory
    free(filename);

    return 0;
}