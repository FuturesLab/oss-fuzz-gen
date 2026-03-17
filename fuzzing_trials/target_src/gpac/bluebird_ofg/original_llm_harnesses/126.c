#include <gpac/isomedia.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_126(const uint8_t *data, size_t size) {
    // Create a temporary file to write the input data
    char tmp_filename[] = "/tmp/fuzz_input.XXXXXX";
    int fd = mkstemp(tmp_filename);
    if (fd == -1) {
        return 0;
    }
    write(fd, data, size);
    close(fd);

    // Initialize variables
    GF_ISOFile *file = gf_isom_open(tmp_filename, GF_ISOM_OPEN_READ, NULL);
    if (!file) {
        // Clean up temporary file
        remove(tmp_filename);
        return 0;
    }

    Bool root_meta = GF_TRUE;
    u32 track_num = 1;
    u32 item_id = 1;
    Bool is_protected = GF_FALSE;
    u32 skip_byte_block = 0;
    u32 crypt_byte_block = 0;
    const u8 *key_info = NULL;
    u32 key_info_size = 0;
    u32 aux_info_type_param = 0;
    u8 *cenc_sai_data = NULL;
    u32 cenc_sai_data_size = 0;
    u32 cenc_sai_alloc_size = 0;

    // Call the function-under-test
    gf_isom_extract_meta_item_get_cenc_info(
        file, root_meta, track_num, item_id, &is_protected,
        &skip_byte_block, &crypt_byte_block, &key_info, &key_info_size,
        &aux_info_type_param, &cenc_sai_data, &cenc_sai_data_size, &cenc_sai_alloc_size
    );

    // Clean up
    if (cenc_sai_data) {
        free(cenc_sai_data);
    }
    gf_isom_close(file);
    remove(tmp_filename);

    return 0;
}