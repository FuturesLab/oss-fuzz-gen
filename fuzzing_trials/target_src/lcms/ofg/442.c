#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

extern long cmsfilelength(FILE *);

int LLVMFuzzerTestOneInput_442(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data to
    FILE *temp_file = tmpfile();
    if (temp_file == NULL) {
        return 0; // If the file can't be created, return early
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, temp_file);

    // Rewind the file to the beginning for reading
    rewind(temp_file);

    // Call the function-under-test
    long length = cmsfilelength(temp_file);

    // Close the temporary file
    fclose(temp_file);

    return 0;
}