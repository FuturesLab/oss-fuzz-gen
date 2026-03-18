#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_40(const uint8_t *data, size_t size) {
    // Write data to a temporary file
    char tmp_filename[] = "/tmp/fuzz_input_XXXXXX";
    int fd = mkstemp(tmp_filename);
    if (fd == -1) {
        return 0;
    }
    FILE *tmp_file = fdopen(fd, "wb");
    if (!tmp_file) {
        close(fd);
        return 0;
    }
    fwrite(data, 1, size, tmp_file);
    fclose(tmp_file);

    // Open the ISO file from the temporary file
    GF_ISOFile *movie = gf_isom_open(tmp_filename, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        remove(tmp_filename);
        return 0;
    }

    u32 trackNumber = size > 0 ? data[0] : 1;  // Ensure trackNumber is not zero
    u32 StreamDescriptionIndex = size > 1 ? data[1] : 1;  // Ensure StreamDescriptionIndex is not zero
    u16 bitDepth = size > 2 ? data[2] : 8;  // Some default bit depth

    gf_isom_set_visual_bit_depth(movie, trackNumber, StreamDescriptionIndex, bitDepth);

    gf_isom_close(movie);

    // Clean up temporary file
    remove(tmp_filename);

    return 0;
}