#include <stdint.h>
#include <stddef.h>
#include <hdf5.h>
#include <string.h>

int LLVMFuzzerTestOneInput_236(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the file name
    if (size < 1) return 0;

    // Create a null-terminated string for the file name
    char filename[256];
    size_t filename_size = (size < 255) ? size : 255;
    memcpy(filename, data, filename_size);
    filename[filename_size] = '\0';

    // Define the flags and file access property list
    unsigned int flags = H5F_ACC_RDONLY; // Read-only access
    hid_t fapl_id = H5P_DEFAULT; // Default file access property list

    // Call the function-under-test
    hid_t file_id = H5Fopen(filename, flags, fapl_id);

    // If the file was successfully opened, close it
    if (file_id >= 0) {
        H5Fclose(file_id);
    }

    return 0;
}