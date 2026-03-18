#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>

int LLVMFuzzerTestOneInput_65(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    GF_ISOTrackID trakID = 1; // Example track ID
    u32 MediaType = GF_ISOM_MEDIA_VISUAL; // Example media type
    u32 TimeScale = 1000; // Example time scale
    u8 *tk_box = (u8 *)malloc(size);
    if (!tk_box) {
        gf_isom_close(movie);
        return 0;
    }

    // Copy data to tk_box
    for (size_t i = 0; i < size; i++) {
        tk_box[i] = data[i];
    }

    u32 tk_box_size = (u32)size;
    Bool udta_only = 0; // Example boolean value

    // Call the function-under-test
    gf_isom_new_track_from_template(movie, trakID, MediaType, TimeScale, tk_box, tk_box_size, udta_only);

    // Clean up
    free(tk_box);
    gf_isom_close(movie);

    return 0;
}