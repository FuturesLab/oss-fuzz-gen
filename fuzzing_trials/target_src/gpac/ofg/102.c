#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for mkstemp, close, and unlink
#include <fcntl.h>  // Include for write
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_102(const uint8_t *data, size_t size) {
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Define the OpenMode and temporary directory
    GF_ISOOpenMode openMode = GF_ISOM_OPEN_READ;
    const char *tmp_dir = "/tmp";

    // Call the function-under-test
    GF_EXPORT *result = gf_isom_open(tmpl, openMode, tmp_dir);

    // Clean up
    if (result != NULL) {
        gf_isom_close(result);
    }
    unlink(tmpl);

    return 0;
}