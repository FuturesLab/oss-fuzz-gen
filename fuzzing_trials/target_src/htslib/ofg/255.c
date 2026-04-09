#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include this for close() and unlink()
#include <fcntl.h>   // Include this for mkstemp()
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_255(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to create valid strings
    if (size < 3) {
        return 0;
    }

    // Create a temporary file to use as the filename
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }
    close(fd);

    // Create a string for mode
    char mode[2];
    mode[0] = (char)data[0];  // Use the first byte for mode
    mode[1] = '\0';

    // Create a htsFormat object
    htsFormat format;
    memset(&format, 0, sizeof(htsFormat));

    // Attempt to open the file using the function-under-test
    htsFile *file = hts_open_format(tmpl, mode, &format);

    // Clean up: close the file and remove the temporary file
    if (file != NULL) {
        hts_close(file);
    }
    unlink(tmpl);

    return 0;
}