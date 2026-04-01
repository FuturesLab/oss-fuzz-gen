#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Include this header for close() and unlink()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_23(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = NULL;
    u32 trackNumber = 1;
    u32 SampleNum = 1;
    FILE *trace = NULL;
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd;

    // Create a temporary file to use as trace
    fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    trace = fdopen(fd, "w+");
    if (!trace) {
        close(fd);
        return 0;
    }

    // Initialize GF_ISOFile
    the_file = gf_isom_open(tmpl, GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        fclose(trace);
        return 0;
    }

    // Fuzz the function
    gf_isom_dump_hint_sample(the_file, trackNumber, SampleNum, trace);

    // Clean up
    gf_isom_close(the_file);
    fclose(trace);
    unlink(tmpl);

    return 0;
}