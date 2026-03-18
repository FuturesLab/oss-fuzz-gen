#include <stdint.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_95(const uint8_t *data, size_t size) {
    gzFile file;
    int flush_value;
    char filename[] = "fuzz_test.gz";

    // Write the data to a temporary file
    FILE *temp_file = fopen(filename, "wb");
    if (temp_file == NULL) {
        return 0;
    }
    fwrite(data, 1, size, temp_file);
    fclose(temp_file);

    // Open the temporary file as a gzFile
    file = gzopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }

    // Try different flush values
    for (flush_value = 0; flush_value <= Z_FINISH; flush_value++) {
        gzflush(file, flush_value);
    }

    gzclose(file);

    // Clean up the temporary file
    remove(filename);

    return 0;
}