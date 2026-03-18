#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    GF_Err err;

    // Ensure the data size is non-zero to avoid unnecessary processing
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to hold the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    write(fd, data, size);
    close(fd);

    // Open the ISO file using the temporary file
    file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        goto cleanup;
    }

    // Call the function-under-test
    gf_isom_guess_specification(file);

cleanup:
    if (file) {
        gf_isom_close(file);
    }
    remove(tmpl);

    return 0;
}