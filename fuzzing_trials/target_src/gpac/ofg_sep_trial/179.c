#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>  // Include the necessary GPAC headers for GF_ISOFile and related functions

int LLVMFuzzerTestOneInput_179(const uint8_t *data, size_t size) {
    GF_ISOFile *file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL); // Create a temporary ISO file
    if (!file) {
        return 0;
    }

    bin128 systemID;
    if (size < sizeof(bin128)) {
        gf_isom_close(file);
        return 0;
    }
    memcpy(systemID, data, sizeof(bin128));

    u32 version = 1; // Set a default version
    u32 KID_count = 1; // Set a default KID count

    bin128 KIDs[1];
    if (size < sizeof(bin128) * 2) {
        gf_isom_close(file);
        return 0;
    }
    memcpy(KIDs, data + sizeof(bin128), sizeof(bin128));

    u8 *pssh_data = (u8 *)malloc(size - sizeof(bin128) * 2);
    if (!pssh_data) {
        gf_isom_close(file);
        return 0;
    }
    memcpy(pssh_data, data + sizeof(bin128) * 2, size - sizeof(bin128) * 2);

    u32 len = size - sizeof(bin128) * 2;
    u32 pssh_mode = 0; // Set a default PSSH mode

    gf_isom_cenc_set_pssh(file, systemID, version, KID_count, KIDs, pssh_data, len, pssh_mode);

    free(pssh_data);
    gf_isom_close(file);

    return 0;
}