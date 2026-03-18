#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_99(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    u32 trackNumber = 1;
    u32 sample_description_index = 1;
    u32 default_sample_group_index = 0;
    u32 id = 0;
    u32 independent = 0;
    Bool full_picture = GF_FALSE;
    u32 x = 0, y = 0, w = 0, h = 0;

    // Create a temporary file to simulate input for GF_ISOFile
    char temp_filename[] = "/tmp/fuzz_input.mp4";
    FILE *temp_file = fopen(temp_filename, "wb");
    if (!temp_file) {
        return 0;
    }
    fwrite(data, 1, size, temp_file);
    fclose(temp_file);

    // Open the temporary file as an ISO media file
    file = gf_isom_open(temp_filename, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_get_tile_info(file, trackNumber, sample_description_index, &default_sample_group_index, &id, &independent, &full_picture, &x, &y, &w, &h);

    // Clean up
    gf_isom_close(file);
    remove(temp_filename);

    return 0;
}