// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_open at isom_read.c:527:13 in isomedia.h
// gf_isom_add_meta_item_sample_ref at meta.c:1806:8 in isomedia.h
// gf_isom_remove_meta_item at meta.c:1879:8 in isomedia.h
// gf_isom_extract_meta_xml at meta.c:68:8 in isomedia.h
// gf_isom_add_meta_item2 at meta.c:1792:8 in isomedia.h
// gf_isom_extract_meta_item at meta.c:494:8 in isomedia.h
// gf_isom_get_meta_item_info at meta.c:131:8 in isomedia.h
// gf_isom_close at isom_read.c:629:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static void write_dummy_file(const char *path, const uint8_t *Data, size_t Size) {
    FILE *file = fopen(path, "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_200(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 4 + sizeof(Bool) * 2) return 0;

    // Create a dummy ISO file object using a valid function or constructor if available
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    if (!isom_file) return 0;

    Bool root_meta = Data[0] % 2;
    u32 track_num = *(u32 *)(Data + 1);
    const char *item_name = "dummy_item";
    u32 item_id = 0;
    u32 item_type = *(u32 *)(Data + 5);
    const char *mime_type = NULL;
    const char *content_encoding = NULL;
    GF_ImageItemProperties *image_props = NULL;
    GF_ISOTrackID tk_id = *(GF_ISOTrackID *)(Data + 9);
    u32 sample_num = *(u32 *)(Data + 13);

    // Write dummy file
    write_dummy_file("./dummy_file", Data, Size);

    // Fuzz gf_isom_add_meta_item_sample_ref
    gf_isom_add_meta_item_sample_ref(isom_file, root_meta, track_num, item_name, &item_id, item_type, mime_type, content_encoding, image_props, tk_id, sample_num);

    // Fuzz gf_isom_remove_meta_item
    u32 item_num = *(u32 *)(Data + 17);
    Bool keep_refs = Data[21] % 2;
    const char *keep_props = NULL;
    gf_isom_remove_meta_item(isom_file, root_meta, track_num, item_num, keep_refs, keep_props);

    // Fuzz gf_isom_extract_meta_xml
    char *outName = "./dummy_output";
    Bool is_binary = Data[22] % 2;
    gf_isom_extract_meta_xml(isom_file, root_meta, track_num, outName, &is_binary);

    // Fuzz gf_isom_add_meta_item2
    Bool self_reference = Data[23] % 2;
    char *resource_path = "./dummy_resource";
    u32 io_item_id = 0;
    const char *URL = NULL;
    const char *URN = NULL;
    gf_isom_add_meta_item2(isom_file, root_meta, track_num, self_reference, resource_path, item_name, &io_item_id, item_type, mime_type, content_encoding, URL, URN, image_props);

    // Fuzz gf_isom_extract_meta_item
    const char *dump_file_name = NULL;
    gf_isom_extract_meta_item(isom_file, root_meta, track_num, item_num, dump_file_name);

    // Fuzz gf_isom_get_meta_item_info
    u32 itemID;
    u32 type;
    u32 protection_scheme;
    u32 protection_scheme_version;
    Bool is_self_reference;
    const char *item_name_out;
    const char *item_mime_type_out;
    const char *item_encoding_out;
    const char *item_url;
    const char *item_urn;
    gf_isom_get_meta_item_info(isom_file, root_meta, track_num, item_num, &itemID, &type, &protection_scheme, &protection_scheme_version, &is_self_reference, &item_name_out, &item_mime_type_out, &item_encoding_out, &item_url, &item_urn);

    // Clean up
    gf_isom_close(isom_file);

    return 0;
}