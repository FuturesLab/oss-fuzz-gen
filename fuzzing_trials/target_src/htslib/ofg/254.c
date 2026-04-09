#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <htslib/hts.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include this for close() and remove()

int LLVMFuzzerTestOneInput_254(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Ensure there's enough data for both strings and format
    }

    // Create temporary file with the fuzz data
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
    fwrite(data, 1, size, file);
    fclose(file);

    // Prepare mode string
    char mode[3];
    mode[0] = (data[size - 2] % 26) + 'a'; // Random lowercase letter
    mode[1] = (data[size - 1] % 26) + 'a'; // Random lowercase letter
    mode[2] = '\0';

    // Prepare htsFormat
    htsFormat format;
    memset(&format, 0, sizeof(htsFormat));
    format.category = data[0] % 3; // Random category
    format.format = data[1] % 5;   // Random format

    // Call the function-under-test
    htsFile *file_handle = hts_open_format(tmpl, mode, &format);

    // Clean up
    if (file_handle) {
        hts_close(file_handle);
    }
    remove(tmpl);

    return 0;
}