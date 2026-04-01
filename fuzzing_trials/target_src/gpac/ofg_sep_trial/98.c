#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>  // Include for close() and unlink()
#include <fcntl.h>   // Include for mkstemp()
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_98(const uint8_t *data, size_t size) {
    GF_ISOFile *file;
    u32 trackNumber = 1;
    u32 sample_description_index = 1;
    u32 default_sample_group_index = 0;
    u32 id = 0;
    u32 independent = 0;
    Bool full_picture = 0;
    u32 x = 0;
    u32 y = 0;
    u32 w = 0;
    u32 h = 0;

    // Create a temporary file to simulate an ISO file
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(tmpl);
        return 0;
    }
    close(fd);

    // Open the ISO file
    file = gf_isom_open(tmpl, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        unlink(tmpl);
        return 0;
    }

    // Call the function-under-test
    gf_isom_get_tile_info(file, trackNumber, sample_description_index, &default_sample_group_index, &id, &independent, &full_picture, &x, &y, &w, &h);

    // Clean up
    gf_isom_close(file);
    unlink(tmpl);

    return 0;
}