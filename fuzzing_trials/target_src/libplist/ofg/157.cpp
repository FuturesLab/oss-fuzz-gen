#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // Include for 'unlink' and 'close'
#include <plist/plist.h>

extern "C" {
    plist_err_t plist_from_openstep(const char *, uint32_t, plist_t *);
}

extern "C" int LLVMFuzzerTestOneInput_157(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to write the fuzz data
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

    // Initialize plist_t variable
    plist_t plist = NULL;

    // Call the function-under-test
    plist_err_t result = plist_from_openstep(tmpl, (uint32_t)size, &plist);

    // Clean up
    if (plist) {
        plist_free(plist);
    }
    unlink(tmpl);

    return 0;
}