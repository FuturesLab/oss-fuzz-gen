#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for close() and mkstemp()
#include <stdint.h> // Include for uint8_t
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_91(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (file == NULL) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Define a mode for opening the file
    const char *mode = "r"; // Read mode

    // Call the function-under-test
    htsFile *hts_file = hts_open(tmpl, mode);

    // Perform any necessary cleanup
    if (hts_file != NULL) {
        hts_close(hts_file);
    }

    // Remove the temporary file
    remove(tmpl);

    return 0;
}