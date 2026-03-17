#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_193(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) return 0;

    Bool root_meta = GF_TRUE;
    u32 meta_track_number = 1;
    u32 imported_track = 1;
    const char *item_name = "test_item";
    u32 item_id = 1;
    GF_ImageItemProperties image_props;
    memset(&image_props, 0, sizeof(GF_ImageItemProperties));
    GF_List *item_extent_refs = gf_list_new();

    gf_isom_iff_create_image_item_from_track(movie, root_meta, meta_track_number, imported_track, item_name, item_id, &image_props, item_extent_refs);

    gf_list_del(item_extent_refs);
    gf_isom_close(movie);

    return 0;
}