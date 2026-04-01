#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for the test
    if (size < sizeof(z_off_t) + sizeof(int)) {
        return 0;
    }

    // Create a temporary file to be used as a gzFile
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write data to the temporary file
    fwrite(data, 1, size, tempFile);
    rewind(tempFile);

    // Open the temporary file with gzopen
    gzFile gzfile = gzdopen(fileno(tempFile), "rb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Extract z_off_t and int from the input data
    z_off_t offset = *((z_off_t *)data);
    int whence = *((int *)(data + sizeof(z_off_t)));

    // Call the function-under-test
    z_off_t result = gzseek(gzfile, offset, whence);

    // Clean up
    gzclose(gzfile);
    fclose(tempFile);

    // Return 0 to indicate the fuzzer should continue
    return 0;
}