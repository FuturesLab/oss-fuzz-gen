#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <unistd.h> // For dup() and fileno()

int LLVMFuzzerTestOneInput_3(const uint8_t *data, size_t size) {
    // Initialize variables
    voidp buffer;
    z_size_t item_size = 1; // size of each item to be read
    z_size_t item_count = size; // number of items to be read
    gzFile file;

    // Allocate memory for the buffer
    buffer = malloc(item_size * item_count);
    if (buffer == NULL) {
        return 0; // Allocation failed, exit early
    }

    // Open a gzFile from the data
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        free(buffer);
        return 0; // Temporary file creation failed, exit early
    }

    file = gzdopen(dup(fileno(temp_file)), "wb");
    if (file == NULL) {
        fclose(temp_file);
        free(buffer);
        return 0; // Opening gzFile failed, exit early
    }

    // Write the data into the gzFile
    gzwrite(file, data, size);
    gzrewind(file); // Rewind to the beginning for reading

    // Call the function-under-test
    gzfread(buffer, item_size, item_count, file);

    // Clean up
    gzclose(file);
    fclose(temp_file);
    free(buffer);

    return 0;
}