#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/hts.h>

int LLVMFuzzerTestOneInput_273(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate an htsFile
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file using hts_open
    htsFile *hts_file = hts_open(tmpl, "r");
    if (hts_file == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    const htsFormat *format = hts_get_format(hts_file);

    // Clean up
    hts_close(hts_file);
    unlink(tmpl);

    return 0;
}