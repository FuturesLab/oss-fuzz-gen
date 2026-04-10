#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For close() and unlink()
#include <htslib/hts.h>
#include <htslib/hfile.h>

// Define a temporary file template
#define TEMP_FILE_TEMPLATE "/tmp/fuzzfileXXXXXX"

int LLVMFuzzerTestOneInput_231(const uint8_t *data, size_t size) {
    char tmpl[] = TEMP_FILE_TEMPLATE;
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Failed to create a temporary file
    }

    // Write the fuzzing data to the temporary file
    FILE *file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0; // Failed to open file descriptor as a FILE*
    }

    fwrite(data, 1, size, file);
    fclose(file);

    // Open the temporary file using hts_open
    hFILE *hfile = hopen(tmpl, "rb");
    if (!hfile) {
        unlink(tmpl); // Clean up the temporary file
        return 0; // Failed to open the file with htslib
    }

    // Prepare the htsFormat structure
    htsFormat format;
    memset(&format, 0, sizeof(format));

    // Call the function-under-test
    hts_detect_format(hfile, &format);

    // Clean up
    hclose(hfile);
    unlink(tmpl); // Remove the temporary file

    return 0;
}