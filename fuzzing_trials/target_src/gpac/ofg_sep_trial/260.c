#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  // For unlink and close
#include <fcntl.h>   // For mkstemp
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_260(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = NULL;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd;
    FILE *file;

    // Create a temporary file and write the input data to it
    fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    file = fdopen(fd, "wb");
    if (!file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the ISO file
    the_file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (!the_file) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    gf_isom_switch_source(the_file, tmpl);

    // Clean up
    gf_isom_close(the_file);
    unlink(tmpl);

    return 0;
}