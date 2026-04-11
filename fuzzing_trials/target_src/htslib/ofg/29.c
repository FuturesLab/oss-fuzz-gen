#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <htslib/hts.h>
#include <htslib/hfile.h>

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size < 1) {
        return 0;
    }

    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the file
    write(fd, data, size);
    close(fd);

    // Open the file using htslib
    hFILE *hfile = hopen(tmpl, "r");
    if (hfile == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Prepare a htsFormat structure
    htsFormat format;
    memset(&format, 0, sizeof(htsFormat));

    // Call the function-under-test
    hts_detect_format2(hfile, tmpl, &format);

    // Clean up
    hclose(hfile);
    unlink(tmpl);

    return 0;
}