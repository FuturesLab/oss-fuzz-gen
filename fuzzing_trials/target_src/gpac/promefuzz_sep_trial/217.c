// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_close at isom_read.c:629:8 in isomedia.h
// gf_isom_remove_user_data_item at isom_write.c:3705:8 in isomedia.h
// gf_isom_set_cenc_protection at drm_sample.c:758:8 in isomedia.h
// gf_isom_cenc_get_sample_aux_info at drm_sample.c:1645:8 in isomedia.h
// gf_isom_set_audio_info at isom_write.c:2373:8 in isomedia.h
// gf_isom_rtp_packet_set_flags at hint_track.c:579:8 in isomedia.h
// gf_isom_update_bitrate at sample_descs.c:1776:8 in isomedia.h
// gf_isom_open at isom_read.c:527:13 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "isomedia.h"

static GF_ISOFile* initialize_iso_file() {
    GF_ISOFile *isom_file = gf_isom_open("./dummy_file", GF_ISOM_OPEN_WRITE, NULL);
    return isom_file;
}

static void cleanup_iso_file(GF_ISOFile *isom_file) {
    if (isom_file) {
        gf_isom_close(isom_file);
    }
}

int LLVMFuzzerTestOneInput_217(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 5 + sizeof(bin128)) return 0;

    GF_ISOFile *isom_file = initialize_iso_file();
    if (!isom_file) return 0;

    u32 trackNumber = *((u32 *) Data);
    u32 UserDataType = *((u32 *) (Data + sizeof(u32)));
    bin128 UUID;
    memcpy(UUID, Data + sizeof(u32) * 2, sizeof(bin128));
    u32 UserDataIndex = *((u32 *) (Data + sizeof(u32) * 2 + sizeof(bin128)));
    
    gf_isom_remove_user_data_item(isom_file, trackNumber, UserDataType, UUID, UserDataIndex);

    if (Size < sizeof(u32) * 9 + sizeof(bin128)) {
        cleanup_iso_file(isom_file);
        return 0;
    }

    u32 sampleDescriptionIndex = *((u32 *) (Data + sizeof(u32) * 3 + sizeof(bin128)));
    u32 scheme_type = *((u32 *) (Data + sizeof(u32) * 4 + sizeof(bin128)));
    u32 scheme_version = *((u32 *) (Data + sizeof(u32) * 5 + sizeof(bin128)));
    u32 default_IsEncrypted = *((u32 *) (Data + sizeof(u32) * 6 + sizeof(bin128)));
    u32 default_crypt_byte_block = *((u32 *) (Data + sizeof(u32) * 7 + sizeof(bin128)));
    u32 default_skip_byte_block = *((u32 *) (Data + sizeof(u32) * 8 + sizeof(bin128)));
    u8 *key_info = (u8 *) (Data + sizeof(u32) * 9 + sizeof(bin128));
    u32 key_info_size = Size - (sizeof(u32) * 9 + sizeof(bin128));
    
    gf_isom_set_cenc_protection(isom_file, trackNumber, sampleDescriptionIndex, scheme_type, scheme_version, default_IsEncrypted, default_crypt_byte_block, default_skip_byte_block, key_info, key_info_size);
    
    if (Size < sizeof(u32) * 10 + sizeof(bin128)) {
        cleanup_iso_file(isom_file);
        return 0;
    }

    u32 sampleNumber = *((u32 *) (Data + sizeof(u32) * 10 + sizeof(bin128)));
    u32 container_type;
    u8 *out_buffer = NULL;
    u32 outSize;
    
    gf_isom_cenc_get_sample_aux_info(isom_file, trackNumber, sampleNumber, sampleDescriptionIndex, &container_type, &out_buffer, &outSize);
    free(out_buffer);

    if (Size < sizeof(u32) * 11 + sizeof(bin128) + sizeof(u8) + sizeof(GF_AudioSampleEntryImportMode)) {
        cleanup_iso_file(isom_file);
        return 0;
    }

    u32 sampleRate = *((u32 *) (Data + sizeof(u32) * 11 + sizeof(bin128)));
    u32 nbChannels = *((u32 *) (Data + sizeof(u32) * 12 + sizeof(bin128)));
    u8 bitsPerSample = *((u8 *) (Data + sizeof(u32) * 13 + sizeof(bin128)));
    GF_AudioSampleEntryImportMode asemode = *((GF_AudioSampleEntryImportMode *) (Data + sizeof(u32) * 13 + sizeof(bin128) + sizeof(u8)));
    
    gf_isom_set_audio_info(isom_file, trackNumber, sampleDescriptionIndex, sampleRate, nbChannels, bitsPerSample, asemode);

    if (Size < sizeof(u32) * 15 + sizeof(bin128) + sizeof(u8) + sizeof(GF_AudioSampleEntryImportMode) + 5) {
        cleanup_iso_file(isom_file);
        return 0;
    }

    u8 PackingBit = *((u8 *) (Data + sizeof(u32) * 14 + sizeof(bin128) + sizeof(u8) + sizeof(GF_AudioSampleEntryImportMode)));
    u8 eXtensionBit = *((u8 *) (Data + sizeof(u32) * 14 + sizeof(bin128) + sizeof(u8) + sizeof(GF_AudioSampleEntryImportMode) + 1));
    u8 MarkerBit = *((u8 *) (Data + sizeof(u32) * 14 + sizeof(bin128) + sizeof(u8) + sizeof(GF_AudioSampleEntryImportMode) + 2));
    u8 disposable_packet = *((u8 *) (Data + sizeof(u32) * 14 + sizeof(bin128) + sizeof(u8) + sizeof(GF_AudioSampleEntryImportMode) + 3));
    u8 IsRepeatedPacket = *((u8 *) (Data + sizeof(u32) * 14 + sizeof(bin128) + sizeof(u8) + sizeof(GF_AudioSampleEntryImportMode) + 4));
    
    gf_isom_rtp_packet_set_flags(isom_file, trackNumber, PackingBit, eXtensionBit, MarkerBit, disposable_packet, IsRepeatedPacket);

    if (Size < sizeof(u32) * 18 + sizeof(bin128) + sizeof(u8) + sizeof(GF_AudioSampleEntryImportMode) + 5) {
        cleanup_iso_file(isom_file);
        return 0;
    }

    u32 average_bitrate = *((u32 *) (Data + sizeof(u32) * 15 + sizeof(bin128) + sizeof(u8) + sizeof(GF_AudioSampleEntryImportMode) + 5));
    u32 max_bitrate = *((u32 *) (Data + sizeof(u32) * 16 + sizeof(bin128) + sizeof(u8) + sizeof(GF_AudioSampleEntryImportMode) + 5));
    u32 decode_buffer_size = *((u32 *) (Data + sizeof(u32) * 17 + sizeof(bin128) + sizeof(u8) + sizeof(GF_AudioSampleEntryImportMode) + 5));
    
    gf_isom_update_bitrate(isom_file, trackNumber, sampleDescriptionIndex, average_bitrate, max_bitrate, decode_buffer_size);

    cleanup_iso_file(isom_file);
    return 0;
}