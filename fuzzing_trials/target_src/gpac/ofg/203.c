#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>
#include <gpac/tools.h>

int LLVMFuzzerTestOneInput_203(const uint8_t *data, size_t size) {
    GF_ISOFile *mov = NULL;
    FILE *trace = NULL;
    Bool skip_init = 0;
    Bool skip_samples = 0;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd;

    // Create a temporary file to store the fuzzing data
    fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        return 0;
    }

    // Open the temporary file as a GF_ISOFile
    mov = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (!mov) {
        close(fd);
        return 0;
    }

    // Call the function-under-test
    gf_isom_dump(mov, trace, skip_init, skip_samples);

    // Clean up
    gf_isom_close(mov);
    close(fd);
    unlink(tmpl);

    return 0;
}