#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>      // For close() and unlink()
#include <fcntl.h>       // For mkstemp()
#include <sys/types.h>   // For ssize_t
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    // Initialize variables before the goto
    GF_ISOFile *isom_file = NULL;
    u32 trackNumber = 1; // Assuming track number 1 for testing
    u32 sampleDescriptionIndex = 1; // Assuming sample description index 1 for testing
    u8 *dsi = NULL;
    u32 dsi_size = 0;
    GF_Err result;

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the ISO file using the temporary file
    isom_file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (!isom_file) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    result = gf_isom_opus_config_get(isom_file, trackNumber, sampleDescriptionIndex, &dsi, &dsi_size);

    // Clean up
    if (dsi) {
        gf_free(dsi);
    }
    gf_isom_close(isom_file);
    unlink(tmpl);

    return 0;
}