// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_apply_box_patch at isom_write.c:8665:8 in isomedia.h
// gf_isom_set_meta_xml at meta.c:698:8 in isomedia.h
// gf_isom_add_meta_item2 at meta.c:1792:8 in isomedia.h
// gf_isom_extract_meta_xml at meta.c:68:8 in isomedia.h
// gf_isom_extract_meta_item_mem at meta.c:500:8 in isomedia.h
// gf_isom_extract_meta_item at meta.c:494:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static void write_dummy_file(const char *filename, const uint8_t *data, size_t size) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_38(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(GF_ISOTrackID) + 2 * sizeof(Bool)) {
        return 0;
    }

    GF_ISOFile *isom_file = NULL;
    GF_ISOTrackID trackID = *((GF_ISOTrackID*)Data);
    Data += sizeof(GF_ISOTrackID);
    Size -= sizeof(GF_ISOTrackID);

    Bool for_fragments = *((Bool*)Data);
    Data += sizeof(Bool);
    Size -= sizeof(Bool);

    Bool root_meta = *((Bool*)Data);
    Data += sizeof(Bool);
    Size -= sizeof(Bool);

    char *filename = "./dummy_file";
    write_dummy_file(filename, Data, Size);

    // Test gf_isom_apply_box_patch
    gf_isom_apply_box_patch(isom_file, trackID, filename, for_fragments);

    // Test gf_isom_set_meta_xml
    gf_isom_set_meta_xml(isom_file, root_meta, trackID, filename, NULL, 0, for_fragments);

    // Test gf_isom_add_meta_item2
    u32 io_item_id = 0;
    gf_isom_add_meta_item2(isom_file, root_meta, trackID, for_fragments, filename, "item_name", &io_item_id, 0, NULL, NULL, NULL, NULL, NULL);

    // Test gf_isom_extract_meta_xml
    Bool is_binary = 0;
    gf_isom_extract_meta_xml(isom_file, root_meta, trackID, filename, &is_binary);

    // Test gf_isom_extract_meta_item_mem
    u8 *out_data = NULL;
    u32 out_size = 0, out_alloc_size = 0;
    const char *mime_type = NULL;
    gf_isom_extract_meta_item_mem(isom_file, root_meta, trackID, trackID, &out_data, &out_size, &out_alloc_size, &mime_type, for_fragments);
    free(out_data);

    // Test gf_isom_extract_meta_item
    gf_isom_extract_meta_item(isom_file, root_meta, trackID, trackID, filename);

    return 0;
}