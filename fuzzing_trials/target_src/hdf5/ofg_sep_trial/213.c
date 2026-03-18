#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

int LLVMFuzzerTestOneInput_213(const uint8_t *data, size_t size) {
    // Define and initialize parameters for H5Fis_accessible
    char *filename;
    hid_t fapl_id = H5P_DEFAULT; // Use the default file access property list

    // Allocate memory for the filename and ensure it is null-terminated
    filename = (char *)malloc(size + 1);
    if (filename == NULL) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(filename, data, size);
    filename[size] = '\0'; // Null-terminate the filename

    // Call the function-under-test
    htri_t result = H5Fis_accessible(filename, fapl_id);

    // Clean up
    free(filename);

    return 0;
}