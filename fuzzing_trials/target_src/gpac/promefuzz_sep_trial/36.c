// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_reset_alt_brands_ex at isom_write.c:3646:8 in isomedia.h
// gf_isom_update_aperture_info at isom_write.c:2179:8 in isomedia.h
// gf_isom_set_meta_xml at meta.c:698:8 in isomedia.h
// gf_isom_set_meta_primary_item at meta.c:1987:8 in isomedia.h
// gf_isom_disable_brand_rewrite at isom_write.c:3512:8 in isomedia.h
// gf_isom_force_64bit_chunk_offset at isom_write.c:2669:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile* create_dummy_iso_file() {
    // Assuming that GF_ISOFile is properly allocated and initialized
    // by some library function. Here we just simulate it.
    GF_ISOFile *file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return file;
}

static void cleanup_iso_file(GF_ISOFile *file) {
    if (file) {
        gf_isom_close(file);
    }
}

int LLVMFuzzerTestOneInput_36(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *iso_file = create_dummy_iso_file();
    if (!iso_file) return 0;

    // Fuzz gf_isom_reset_alt_brands_ex
    Bool leave_empty = Data[0] % 2;
    gf_isom_reset_alt_brands_ex(iso_file, leave_empty);

    // Fuzz gf_isom_update_aperture_info
    u32 trackNumber = (Size > 1) ? Data[1] : 0;
    Bool remove_aperture = (Size > 2) ? Data[2] % 2 : GF_FALSE;
    gf_isom_update_aperture_info(iso_file, trackNumber, remove_aperture);

    // Fuzz gf_isom_set_meta_xml
    Bool root_meta = (Size > 3) ? Data[3] % 2 : GF_FALSE;
    u32 track_num = (Size > 4) ? Data[4] : 0;
    char *XMLFileName = NULL;
    unsigned char *xml_data = (unsigned char *)Data;
    u32 xml_data_size = (Size > 5) ? Size - 5 : 0;
    Bool IsBinaryXML = (Size > 6) ? Data[5] % 2 : GF_FALSE;
    gf_isom_set_meta_xml(iso_file, root_meta, track_num, XMLFileName, xml_data, xml_data_size, IsBinaryXML);

    // Fuzz gf_isom_set_meta_primary_item
    u32 item_num = (Size > 7) ? Data[6] : 1;
    gf_isom_set_meta_primary_item(iso_file, root_meta, track_num, item_num);

    // Fuzz gf_isom_disable_brand_rewrite
    Bool do_disable = (Size > 8) ? Data[7] % 2 : GF_FALSE;
    gf_isom_disable_brand_rewrite(iso_file, do_disable);

    // Fuzz gf_isom_force_64bit_chunk_offset
    Bool set_on = (Size > 9) ? Data[8] % 2 : GF_FALSE;
    gf_isom_force_64bit_chunk_offset(iso_file, set_on);

    cleanup_iso_file(iso_file);
    return 0;
}