#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_53(const uint8_t *data, size_t size) {
    GF_ISOFile *the_file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    u32 trackNumber = size > 0 ? data[0] : 1;
    u32 desc_index = size > 1 ? data[1] : 1;
    u32 scheme_type = size > 2 ? data[2] : 1;
    u32 scheme_version = size > 3 ? data[3] : 1;
    u32 default_IsEncrypted = size > 4 ? data[4] : 0;
    u32 default_crypt_byte_block = size > 5 ? data[5] : 0;
    u32 default_skip_byte_block = size > 6 ? data[6] : 0;

    u8 *key_info = NULL;
    u32 key_info_size = 0;

    if (size > 7) {
        key_info_size = size - 7;
        key_info = (u8 *)malloc(key_info_size);
        if (key_info) {
            for (u32 i = 0; i < key_info_size; i++) {
                key_info[i] = data[7 + i];
            }
        }
    }

    gf_isom_set_cenc_protection(the_file, trackNumber, desc_index, scheme_type, scheme_version, 
                                default_IsEncrypted, default_crypt_byte_block, default_skip_byte_block, 
                                key_info, key_info_size);

    if (key_info) {
        free(key_info);
    }

    gf_isom_close(the_file);

    return 0;
}