#include <stdint.h>
#include <stddef.h>
#include <zlib.h>
#include <stdio.h>

// Custom function to open a gzFile from memory
gzFile open_gzfile_from_memory(const uint8_t *data, size_t size) {
    // Create a temporary file to write the data
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return NULL;
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, tempFile);
    rewind(tempFile);

    // Open the temporary file as a gzFile
    gzFile gzfile = gzdopen(fileno(tempFile), "rb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return NULL;
    }

    return gzfile;
}

int LLVMFuzzerTestOneInput_115(const uint8_t *data, size_t size) {
    // Ensure the data size is reasonable
    if (size == 0) {
        return 0;
    }

    // Open a gzFile from the input data
    gzFile file = open_gzfile_from_memory(data, size);
    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test
    off_t offset = gzoffset(file);

    // Close the gzFile
    gzclose(file);

    return 0;
}