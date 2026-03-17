#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For mkstemp, write, close, remove
#include <gpac/isomedia.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_261(const uint8_t *data, size_t size) {
    GF_ISOFile *file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!file) {
        return 0;
    }

    GF_ISOTrackID globalTrackID = 1; // Assuming track ID 1 for testing

    // Create a temporary file to simulate the box patch file
    char tmpl[] = "/tmp/box_patchXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        gf_isom_close(file);
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        gf_isom_close(file);
        return 0;
    }
    close(fd);

    Bool for_fragments = 1; // Assuming true for fragments

    // Call the function-under-test
    gf_isom_apply_box_patch(file, globalTrackID, tmpl, for_fragments);

    // Clean up
    gf_isom_close(file);
    remove(tmpl);

    return 0;
}

#ifdef __cplusplus
}
#endif