#include "/src/gpac/include/gpac/isomedia.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_137(const uint8_t *data, size_t size) {
    // Create a temporary file to simulate file input for gf_isom_open
    char filename[] = "/tmp/fuzz_isom_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(filename);
        return 0;
    }

    // Close the file descriptor
    close(fd);

    // Open the ISO media file using gf_isom_open
    GF_ISOFile *file = gf_isom_open(filename, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        unlink(filename);
        return 0;
    }

    Bool root_meta = 1; // Arbitrary non-NULL value
    u32 track_num = 1;  // Arbitrary non-NULL value
    u32 item_id = 1;    // Arbitrary non-NULL value

    Bool is_protected = 0;
    u32 skip_byte_block = 0;
    u32 crypt_byte_block = 0;
    const u8 *key_info = NULL;
    u32 key_info_size = 0;
    u32 aux_info_type_param = 0;
    u8 *cenc_sai_data = NULL;
    u32 cenc_sai_data_size = 0;
    u32 cenc_sai_alloc_size = 0;

    gf_isom_extract_meta_item_get_cenc_info(
        file,
        root_meta,
        track_num,
        item_id,
        &is_protected,
        &skip_byte_block,
        &crypt_byte_block,
        &key_info,
        &key_info_size,
        &aux_info_type_param,
        &cenc_sai_data,
        &cenc_sai_data_size,
        &cenc_sai_alloc_size
    );

    if (cenc_sai_data) {
        free(cenc_sai_data);
    }

    gf_isom_close(file);

    // Remove the temporary file
    unlink(filename);

    return 0;
}