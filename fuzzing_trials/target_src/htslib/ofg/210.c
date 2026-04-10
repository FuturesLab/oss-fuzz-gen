#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/hts.h>
#include <htslib/hfile.h>
#include <string.h>

int LLVMFuzzerTestOneInput_210(const uint8_t *data, size_t size) {
    if (size < 3) {
        return 0; // Ensure there is enough data for mode and format
    }

    // Create a temporary file to write the data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0; // Cannot create temp file
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        return 0; // Failed to write all data
    }
    close(fd);

    // Open the temporary file using hts_hopen
    hFILE *hfile = hopen(tmpl, "r");
    if (hfile == NULL) {
        return 0; // Failed to open file
    }

    // Prepare mode and format strings
    const char *mode = "r";
    const char *format = "b"; // Assuming binary format for testing

    // Call the function-under-test
    htsFile *htsfile = hts_hopen(hfile, mode, format);

    // Clean up
    if (htsfile != NULL) {
        hts_close(htsfile);
    }
    hclose(hfile);
    unlink(tmpl); // Remove the temporary file

    return 0;
}