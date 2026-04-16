#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "hdf5.h"

int LLVMFuzzerTestOneInput_7(const uint8_t *data, size_t size) {
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
        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function H5Fclose with H5Freset_page_buffering_stats
        H5Freset_page_buffering_stats(file_id);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR
    }

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_7(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
