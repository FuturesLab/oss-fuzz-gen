#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_155(const uint8_t *data, size_t size) {
    // Create a temporary ISO file using the input data
    // Use a temporary directory for the ISO file creation
    const char *tmp_dir = "/tmp"; // Example temporary directory
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, tmp_dir);

    // Ensure the movie is not NULL
    if (movie == NULL) {
        return 0;
    }

    // Declare and initialize variables for the function parameters
    u32 trackNumber = 1; // Example track number
    u32 StreamDescriptionIndex = 1; // Example stream description index
    Bool remove = GF_FALSE; // Example boolean value
    Bool all_ref_pics_intra = GF_TRUE; // Example boolean value
    Bool intra_pred_used = GF_FALSE; // Example boolean value
    u32 max_ref_per_pic = 1; // Example maximum reference per picture

    // Call the function-under-test
    gf_isom_set_image_sequence_coding_constraints(movie, trackNumber, StreamDescriptionIndex, remove, all_ref_pics_intra, intra_pred_used, max_ref_per_pic);

    // Close the movie file and clean up
    gf_isom_close(movie);

    return 0;
}