#include <stdint.h>
#include <stdio.h>
#include <zlib.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h> // Include this header for off64_t
#include <inttypes.h>  // Include this header for PRId64

int LLVMFuzzerTestOneInput_124(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    FILE *tempFile = tmpfile();
    if (tempFile == NULL) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, tempFile);
    rewind(tempFile);

    // Open the temporary file as a gzFile
    gzFile gzfile = gzdopen(fileno(tempFile), "rb");
    if (gzfile == NULL) {
        fclose(tempFile);
        return 0;
    }

    // Call the function-under-test
    off_t position = gztell(gzfile); // Use off_t and gztell instead of off64_t and gztell64

    // Print the position for debugging purposes
    printf("Current position in the gzFile: %" PRId64 "\n", (int64_t)position);

    // Clean up
    gzclose(gzfile);
    fclose(tempFile);

    return 0;
}