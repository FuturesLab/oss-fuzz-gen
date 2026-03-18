#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>
#include <unistd.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Initialize variables for gzfread function
    voidp buffer;
    z_size_t sizeToRead = 1; // Arbitrary non-zero size to read
    z_size_t nmemb = size / sizeToRead; // Number of elements to read
    gzFile file;

    // Allocate memory for the buffer
    buffer = malloc(sizeToRead * nmemb);
    if (buffer == NULL) {
        return 0;
    }

    // Open a gzFile in memory from the input data
    FILE *tmp = tmpfile();
    if (tmp == NULL) {
        free(buffer);
        return 0;
    }
    
    file = gzdopen(dup(fileno(tmp)), "wb");
    if (file == NULL) {
        fclose(tmp);
        free(buffer);
        return 0;
    }

    // Write the input data to the gzFile
    gzwrite(file, data, size);
    gzrewind(file);

    // Reopen the gzFile for reading
    gzclose(file);
    file = gzdopen(dup(fileno(tmp)), "rb");
    if (file == NULL) {
        fclose(tmp);
        free(buffer);
        return 0;
    }

    // Call the function-under-test
    gzfread(buffer, sizeToRead, nmemb, file);

    // Clean up
    gzclose(file);
    fclose(tmp);
    free(buffer);

    return 0;
}