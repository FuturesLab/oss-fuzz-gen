#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_6(const uint8_t *data, size_t size) {
    // Write data to a temporary file
    FILE *temp_file = tmpfile();
    if (!temp_file) {
        return 0;
    }
    fwrite(data, 1, size, temp_file);
    fseek(temp_file, 0, SEEK_SET);

    // Open the temporary file as an ISO media file
    GF_ISOFile *the_file = gf_isom_open(temp_file, GF_ISOM_OPEN_READ, NULL);
    if (the_file == NULL) {
        fclose(temp_file);
        return 0;
    }

    // Initialize trackNumber and unpack variables
    u32 trackNumber = 1; // Use a valid track number, assuming at least one track exists
    Bool unpack = GF_TRUE; // Set unpack to true

    // Call the function-under-test
    gf_isom_set_cts_packing(the_file, trackNumber, unpack);

    // Clean up
    gf_isom_close(the_file);
    fclose(temp_file);

    return 0;
}