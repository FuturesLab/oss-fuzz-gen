#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>

int LLVMFuzzerTestOneInput_8(const uint8_t *data, size_t size) {
    // Write the input data to a temporary file
    char tmp_filename[] = "/tmp/fuzz_input.mp4";
    FILE *tmp_file = fopen(tmp_filename, "wb");
    if (!tmp_file) {
        return 0;
    }
    fwrite(data, 1, size, tmp_file);
    fclose(tmp_file);

    // Open the temporary file as an ISO media file
    GF_ISOFile *file = gf_isom_open(tmp_filename, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        return 0;
    }

    // Set root_meta to a non-null value
    Bool root_meta = 1; // or use 0, as both are valid Bool values

    // Set track_num to a non-zero value
    u32 track_num = 1; // Could be any positive integer

    // Call the function-under-test
    gf_isom_get_meta_primary_item_id(file, root_meta, track_num);

    // Clean up
    gf_isom_close(file);

    // Remove the temporary file
    remove(tmp_filename);

    return 0;
}