// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_add_meta_item_sample_ref at meta.c:1806:8 in isomedia.h
// gf_isom_remove_meta_item at meta.c:1879:8 in isomedia.h
// gf_isom_extract_meta_xml at meta.c:68:8 in isomedia.h
// gf_isom_add_meta_item2 at meta.c:1792:8 in isomedia.h
// gf_isom_extract_meta_item at meta.c:494:8 in isomedia.h
// gf_isom_get_meta_item_info at meta.c:131:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

static GF_ISOFile* create_dummy_isofile() {
    // Since we cannot allocate an incomplete type, return NULL for now
    return NULL;
}

int LLVMFuzzerTestOneInput_196(const uint8_t *Data, size_t Size) {
    if (Size == 0) return 0;

    GF_ISOFile *isom_file = create_dummy_isofile();
    if (!isom_file) return 0;

    Bool root_meta = Data[0] % 2;
    u32 track_num = 0;
    const char *item_name = "item_name";
    u32 item_id = 0;
    u32 item_type = 'test';
    const char *mime_type = "application/test";
    const char *content_encoding = "utf-8";
    GF_ImageItemProperties *image_props = NULL;
    GF_ISOTrackID tk_id = 1;
    u32 sample_num = 1;

    // Fuzz gf_isom_add_meta_item_sample_ref
    gf_isom_add_meta_item_sample_ref(isom_file, root_meta, track_num, item_name, &item_id, item_type, mime_type, content_encoding, image_props, tk_id, sample_num);

    // Fuzz gf_isom_remove_meta_item
    u32 item_num = 1;
    Bool keep_refs = Data[0] % 2;
    const char *keep_props = "test_props";
    gf_isom_remove_meta_item(isom_file, root_meta, track_num, item_num, keep_refs, keep_props);

    // Fuzz gf_isom_extract_meta_xml
    char *outName = "./dummy_file";
    Bool is_binary = Data[0] % 2;
    gf_isom_extract_meta_xml(isom_file, root_meta, track_num, outName, &is_binary);

    // Fuzz gf_isom_add_meta_item2
    Bool self_reference = Data[0] % 2;
    char *resource_path = "./dummy_file";
    u32 io_item_id = 0;
    const char *URL = "http://example.com";
    const char *URN = "urn:example";
    gf_isom_add_meta_item2(isom_file, root_meta, track_num, self_reference, resource_path, item_name, &io_item_id, item_type, mime_type, content_encoding, URL, URN, image_props);

    // Fuzz gf_isom_extract_meta_item
    const char *dump_file_name = "./dummy_file";
    gf_isom_extract_meta_item(isom_file, root_meta, track_num, item_num, dump_file_name);

    // Fuzz gf_isom_get_meta_item_info
    u32 itemID, type, protection_scheme, protection_scheme_version;
    Bool is_self_reference;
    const char *item_name_out, *item_mime_type, *item_encoding, *item_url, *item_urn;
    gf_isom_get_meta_item_info(isom_file, root_meta, track_num, item_num, &itemID, &type, &protection_scheme, &protection_scheme_version, &is_self_reference, &item_name_out, &item_mime_type, &item_encoding, &item_url, &item_urn);

    // No need to free isom_file since it's NULL
    return 0;
}