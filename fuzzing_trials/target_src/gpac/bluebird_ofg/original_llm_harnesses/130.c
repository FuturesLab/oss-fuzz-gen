#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_130(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    FILE *temp_file = tmpfile();
    if (!temp_file) {
        return 0;
    }

    // Write data to the temporary file
    if (fwrite(data, 1, size, temp_file) != size) {
        fclose(temp_file);
        return 0;
    }

    // Rewind the file pointer to the beginning of the file
    rewind(temp_file);

    // Open the ISO media file using the temporary file
    GF_ISOFile *file = gf_isom_open(temp_file, GF_ISOM_OPEN_READ, NULL);
    if (file == NULL) {
        fclose(temp_file);
        return 0;
    }

    Bool root_meta = GF_TRUE;  // or GF_FALSE, try both variations
    u32 track_num = 1;  // Start with track number 1, adjust if needed

    // Call the function under test
    gf_isom_get_meta_type(file, root_meta, track_num);

    // Clean up
    gf_isom_close(file);
    fclose(temp_file);

    return 0;
}