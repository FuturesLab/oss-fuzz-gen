#include <stdint.h>
#include <stdlib.h>
#include <unistd.h> // Include this for the unlink function
#include <fcntl.h>  // Include this for the mkstemp function
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_82(const uint8_t *data, size_t size) {
    GF_ISOFile *isom_file = NULL;
    u32 trackNumber = 1; // Assuming a track number for testing
    u32 sampleDescriptionIndex = 1; // Assuming a sample description index for testing
    u8 *dsi = NULL;
    u32 dsi_size = 0;

    // Create a temporary file to simulate an ISO media file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }
    write(fd, data, size);
    close(fd);

    // Open the ISO media file
    isom_file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (isom_file == NULL) {
        goto cleanup;
    }

    // Call the function-under-test
    gf_isom_opus_config_get(isom_file, trackNumber, sampleDescriptionIndex, &dsi, &dsi_size);

cleanup:
    if (isom_file != NULL) {
        gf_isom_close(isom_file);
    }
    if (dsi != NULL) {
        free(dsi);
    }
    unlink(tmpl); // Clean up the temporary file

    return 0;
}