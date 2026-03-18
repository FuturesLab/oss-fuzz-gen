#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Include for close() and write()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_262(const uint8_t *data, size_t size) {
    GF_ISOFile *file = gf_isom_open("sample.mp4", GF_ISOM_OPEN_READ, NULL);
    if (file == NULL) {
        return 0;
    }

    GF_ISOTrackID globalTrackID = 1; // Assuming a valid track ID for simplicity

    // Create a temporary file to store the box patch data
    char tmpl[] = "/tmp/boxpatchXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd < 0) {
        gf_isom_close(file);
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        gf_isom_close(file);
        return 0;
    }
    close(fd);

    Bool for_fragments = GF_FALSE; // or GF_TRUE, depending on what you want to test

    // Call the function under test
    gf_isom_apply_box_patch(file, globalTrackID, tmpl, for_fragments);

    // Clean up
    gf_isom_close(file);
    remove(tmpl);

    return 0;
}