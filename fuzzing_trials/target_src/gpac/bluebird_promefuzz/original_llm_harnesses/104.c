// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_release_segment at isom_read.c:3459:8 in isomedia.h
// gf_isom_remove_root_od at isom_write.c:165:8 in isomedia.h
// gf_isom_flush_fragments at movie_fragments.c:1468:8 in isomedia.h
// gf_isom_set_storage_mode at isom_write.c:2636:8 in isomedia.h
// gf_isom_set_removed_bytes at isom_read.c:3185:8 in isomedia.h
// gf_isom_sdp_clean at hint_track.c:884:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "isomedia.h"

// Dummy definition of GF_ISOFile since the actual structure is not available
struct __tag_isom {
    GF_Err LastError;
    GF_ISOOpenMode openMode;
    u8 storageMode;
    u64 next_flush_chunk_time;
    s64 read_byte_offset;
    u64 bytes_removed;
    GF_ISOCompressMode compress_mode;
    u32 compress_flags;
    u32 pad_cmov;
    void (*progress_cbk)(void *udta, u64 nb_done, u64 nb_total);
    void *progress_cbk_udta;
    u64 current_top_box_start;
    Bool signal_frag_bounds;
    Bool sample_groups_in_traf;
    u32 FragmentsFlags;
    u32 NextMoofNumber;
    Bool use_segments, moof_first, append_segment, force_moof_base_offset;
    u32 write_styp;
    Bool in_sidx_write;
    Bool is_index_segment;
    Bool single_moof_mode;
    u32 single_moof_state;
    Bool force_sidx_v1;
    Bool store_traf_map;
    u64 root_sidx_start_offset, root_sidx_end_offset;
    u64 sidx_start_offset, sidx_end_offset;
    u64 styp_start_offset;
    u64 mdat_end_offset;
    u32 sidx_pts_store_alloc, sidx_pts_store_count;
    u64 *sidx_pts_store, *sidx_pts_next_store;
    u64 main_sidx_end_pos;
    Bool has_pssh_moof;
    s32 es_id_default_sync;
    Bool is_smooth;
    GF_Err (*on_block_out)(void *usr_data, u8 *block, u32 block_size, void *cbk_data, u32 cbk_magic);
    GF_Err (*on_block_patch)(void *usr_data, u8 *block, u32 block_size, u64 block_offset, Bool is_insert);
    void (*on_last_block_start)(void *usr_data);
    void *on_block_out_usr_data;
    u32 on_block_out_block_size;
    u64 fragmented_file_pos;
    u8 *block_buffer;
    u32 block_buffer_size;
    Bool blocks_sent;
    u32 nb_box_init_seg;
    Bool no_inplace_rewrite;
    u32 padding;
    u64 original_moov_offset, original_meta_offset, first_data_toplevel_offset, first_data_toplevel_size;
};

static GF_ISOFile* create_dummy_isofile() {
    GF_ISOFile *isofile = (GF_ISOFile *)malloc(sizeof(struct __tag_isom));
    if (!isofile) return NULL;
    memset(isofile, 0, sizeof(struct __tag_isom));
    isofile->FragmentsFlags = 0; // Ensure valid flag for testing
    return isofile;
}

static void destroy_dummy_isofile(GF_ISOFile *isofile) {
    if (isofile) {
        free(isofile);
    }
}

int LLVMFuzzerTestOneInput_104(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    GF_ISOFile *isofile = create_dummy_isofile();
    if (!isofile) return 0;

    // Fuzz gf_isom_flush_fragments
    Bool last_segment = Data[0] % 2;
    gf_isom_flush_fragments(isofile, last_segment);

    // Fuzz gf_isom_set_storage_mode
    if (Size > 1) {
        GF_ISOStorageMode storage_mode = (GF_ISOStorageMode)Data[1];
        gf_isom_set_storage_mode(isofile, storage_mode);
    }

    // Fuzz gf_isom_set_removed_bytes
    if (Size > 9) {
        u64 bytes_removed;
        memcpy(&bytes_removed, &Data[2], sizeof(u64));
        gf_isom_set_removed_bytes(isofile, bytes_removed);
    }

    // Fuzz gf_isom_sdp_clean
    gf_isom_sdp_clean(isofile);

    // Fuzz gf_isom_release_segment
    if (Size > 10) {
        Bool reset_tables = Data[10] % 2;
        gf_isom_release_segment(isofile, reset_tables);
    }

    // Fuzz gf_isom_remove_root_od
    gf_isom_remove_root_od(isofile);

    destroy_dummy_isofile(isofile);
    return 0;
}