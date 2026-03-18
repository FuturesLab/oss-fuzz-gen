#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_13(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    GF_Err err;

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        remove(tmpl);
        return 0;
    }
    close(fd);

    // Open the temporary file as an ISO file
    file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (file == NULL) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    err = gf_isom_guess_specification(file);

    // Clean up
    gf_isom_close(file);
    remove(tmpl);

    return 0;
}