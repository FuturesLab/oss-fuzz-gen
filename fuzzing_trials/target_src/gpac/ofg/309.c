#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h> // Ensure constants are included
#include <gpac/internal/isomedia_dev.h> // Include internal header for GF_ISOM_BOX_TYPE_MP4V
#include <stdio.h>

int LLVMFuzzerTestOneInput_309(const uint8_t *data, size_t size) {
    // Write the input data to a temporary file
    FILE *tempFile = fopen("temp_input.mp4", "wb");
    if (!tempFile) {
        return 0;
    }
    fwrite(data, 1, size, tempFile);
    fclose(tempFile);

    // Open the temporary file as an ISO media file
    GF_ISOFile *movie = gf_isom_open("temp_input.mp4", GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1; // Assuming track number 1 for fuzzing
    const char *URLname = "http://example.com/sample";
    const char *URNname = "urn:example:sample";
    GF_GenericSampleDescription udesc;
    u32 outDescriptionIndex = 0;

    // Ensure the movie is not NULL
    if (movie == NULL) {
        return 0;
    }

    // Initialize the sample description with some dummy values
    memset(&udesc, 0, sizeof(GF_GenericSampleDescription));
    udesc.codec_tag = GF_ISOM_BOX_TYPE_MP4V; // Correctly use the codec tag
    udesc.vendor_code = 1; // Assuming this is a suitable replacement for dataReferenceIndex

    // Call the function under test
    gf_isom_new_generic_sample_description(movie, trackNumber, URLname, URNname, &udesc, &outDescriptionIndex);

    // Clean up
    gf_isom_close(movie);
    remove("temp_input.mp4"); // Remove the temporary file

    return 0;
}