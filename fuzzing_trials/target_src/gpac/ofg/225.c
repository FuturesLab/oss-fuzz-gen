#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_225(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = NULL;
    u32 trackNumber;
    char *text = NULL;

    // Ensure size is sufficient to extract trackNumber and text
    if (size < sizeof(u32) + 1) {
        return 0;
    }

    // Initialize trackNumber from the input data
    trackNumber = *((u32 *)data);

    // Allocate and initialize text from the remaining input data
    text = (char *)malloc(size - sizeof(u32) + 1);
    if (!text) {
        return 0;
    }
    memcpy(text, data + sizeof(u32), size - sizeof(u32));
    text[size - sizeof(u32)] = '\0';  // Null-terminate the text

    // Create a dummy GF_ISOFile object
    the_file = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);

    // Call the function under test
    gf_isom_sdp_add_track_line(the_file, trackNumber, text);

    // Clean up
    if (the_file) {
        gf_isom_close(the_file);
    }
    free(text);

    return 0;
}