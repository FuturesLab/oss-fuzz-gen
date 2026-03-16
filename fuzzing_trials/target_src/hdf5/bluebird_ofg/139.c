#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_139(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to contain a non-empty string and additional parameters
    if (size < 5) {
        return 0;
    }

    // Use the data to create a null-terminated string for the file name
    char filename[256];
    size_t filename_len = (size < sizeof(filename) - 1) ? size : sizeof(filename) - 1;
    memcpy(filename, data, filename_len);
    filename[filename_len] = '\0';

    // Extract the flags and fapl_id from the data
    unsigned int flags = (unsigned int)data[filename_len % size];
    hid_t fapl_id = (hid_t)data[(filename_len + 1) % size];

    // Call the function-under-test
    hid_t file_id = H5Fopen(filename, flags, fapl_id);

    // If the file was successfully opened, close it
    if (file_id >= 0) {

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from H5Fopen to H5Aget_type

    hid_t ret_H5Aget_type_ixnti = H5Aget_type(file_id);

    // End mutation: Producer.APPEND_MUTATOR

        H5Fclose(file_id);
    }
    return 0;
}