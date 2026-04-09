#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>    // For close() and unlink()
#include <fcntl.h>     // For open() and mkstemp()
#include "htslib/hts.h"
#include "htslib/hfile.h"  // For hFILE, hopen, hclose

int LLVMFuzzerTestOneInput_185(const uint8_t *data, size_t size) {
    // Create a temporary file to write the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the temporary file using hopen
    struct hFILE *hfile = hopen(tmpl, "r");
    if (hfile == NULL) {
        unlink(tmpl);
        return 0;
    }

    // Initialize htsFormat structure
    htsFormat format;
    memset(&format, 0, sizeof(htsFormat));

    // Call the function-under-test
    hts_detect_format(hfile, &format);

    // Close the file and remove the temporary file
    hclose(hfile);
    unlink(tmpl);

    return 0;
}