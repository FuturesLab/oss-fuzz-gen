#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <string.h> // Include for memcpy

int LLVMFuzzerTestOneInput_307(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    FILE *temp_file = fopen("temp.mp4", "wb");
    if (!temp_file) {
        return 0;
    }

    // Write the input data to the temporary file
    fwrite(data, 1, size, temp_file);
    fclose(temp_file);

    // Open the temporary file using GPAC library
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (the_file == NULL) {
        return 0;
    }

    u32 trackNumber = 1; // Assuming at least one track exists
    u8 IsRandomAccessPoint = 1; // Set to a non-zero value

    // Call the function-under-test
    gf_isom_end_hint_sample(the_file, trackNumber, IsRandomAccessPoint);

    // Clean up
    gf_isom_close(the_file);

    // Remove the temporary file
    remove("temp.mp4");

    return 0;
}