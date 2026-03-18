#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    // Create a temporary file to use with gzopen
    const char *temp_filename = "temp.gz";
    FILE *temp_file = fopen(temp_filename, "wb");
    if (temp_file == NULL) {
        return 0;
    }
    fclose(temp_file);

    // Open the temporary file with gzopen
    gzFile gz_file = gzopen(temp_filename, "wb");
    if (gz_file == NULL) {
        return 0;
    }

    // Ensure the input data is null-terminated
    char *input_str = (char *)malloc(size + 1);
    if (input_str == NULL) {
        gzclose(gz_file);
        return 0;
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    // Call the function-under-test
    gzputs(gz_file, input_str);
    gzclose(gz_file);

    // Reopen the file for reading
    gz_file = gzopen(temp_filename, "rb");
    if (gz_file == NULL) {
        free(input_str);
        return 0;
    }

    // Read back the content
    char buffer[1024];
    int bytes_read = gzread(gz_file, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0'; // Null-terminate the buffer
        // Compare the input and output
        if (strcmp(input_str, buffer) != 0) {
            // Log a message if the content doesn't match
            fprintf(stderr, "Mismatch between input and output\n");
        }
    }

    // Clean up
    free(input_str);
    gzclose(gz_file);
    remove(temp_filename);

    return 0;
}