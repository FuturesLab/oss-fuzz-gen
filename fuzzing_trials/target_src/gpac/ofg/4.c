#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Include for close() and remove()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = NULL;
    u32 trackNumber = 1; // Example track number
    u32 HintDescriptionIndex = 1; // Example hint description index
    u32 TimeOffset = 0; // Example time offset

    // Create a temporary file to simulate an ISO media file
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

    // Write the fuzz data to the file
    fwrite(data, 1, size, file);
    fclose(file);

    // Open the ISO media file
    the_file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (!the_file) {
        remove(tmpl);
        return 0;
    }

    // Call the function-under-test
    gf_isom_rtp_set_time_offset(the_file, trackNumber, HintDescriptionIndex, TimeOffset);

    // Clean up
    gf_isom_close(the_file);
    remove(tmpl);

    return 0;
}