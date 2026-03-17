#include <stdint.h>
#include <stdlib.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_166(const uint8_t *data, size_t size) {
    if (size < sizeof(GF_ISOTrackID) + sizeof(u32) * 2 + sizeof(Bool) + 1) {
        return 0; // Ensure there's enough data for all parameters
    }

    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0; // Fail gracefully if the movie cannot be opened
    }

    GF_ISOTrackID trakID = *(GF_ISOTrackID *)data;
    data += sizeof(GF_ISOTrackID);

    u32 MediaType = *(u32 *)data;
    data += sizeof(u32);

    u32 TimeScale = *(u32 *)data;
    data += sizeof(u32);

    Bool udta_only = *(Bool *)data;
    data += sizeof(Bool);

    u32 tk_box_size = size - (sizeof(GF_ISOTrackID) + sizeof(u32) * 2 + sizeof(Bool));
    u8 *tk_box = (u8 *)data;


    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from gf_isom_open to gf_isom_flush_fragments
    Bool ret_gf_isom_has_keep_utc_times_cakmb = gf_isom_has_keep_utc_times(movie);

    GF_Err ret_gf_isom_flush_fragments_pvkfx = gf_isom_flush_fragments(movie, ret_gf_isom_has_keep_utc_times_cakmb);

    // End mutation: Producer.APPEND_MUTATOR

    gf_isom_new_track_from_template(movie, trakID, MediaType, TimeScale, tk_box, tk_box_size, udta_only);

    gf_isom_close(movie);

    return 0;
}