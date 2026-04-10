#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  // Include for mkstemp and close
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_226(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to use with hts_open
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }

    // Write the data to the temporary file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the file with hts_open
    htsFile *hts_file = hts_open(tmpl, "r");
    if (hts_file == NULL) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    hts_close(hts_file);

    // Clean up
    remove(tmpl);

    return 0;
}