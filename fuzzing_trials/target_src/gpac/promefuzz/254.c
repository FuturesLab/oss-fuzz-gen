// This fuzz driver is generated for library gpac, aiming to fuzz the following functions:
// gf_isom_new_mpeg4_description at isom_write.c:933:8 in isomedia.h
// gf_isom_change_mpeg4_description at isom_write.c:1732:8 in isomedia.h
// gf_isom_get_esd at isom_read.c:1386:9 in isomedia.h
// gf_isom_get_pcm_config at sample_descs.c:1972:8 in isomedia.h
// gf_isom_get_visual_info at isom_read.c:3821:8 in isomedia.h
// gf_isom_add_track_to_root_od at isom_write.c:136:8 in isomedia.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "isomedia.h"

static GF_ISOFile *create_dummy_isofile() {
    return NULL; // Return NULL as we cannot instantiate GF_ISOFile without its definition
}

static GF_ESD *create_dummy_esd() {
    GF_ESD *esd = (GF_ESD *)malloc(sizeof(GF_ESD));
    if (!esd) return NULL;
    memset(esd, 0, sizeof(GF_ESD));
    return esd;
}

static void cleanup(GF_ISOFile *isofile, GF_ESD *esd) {
    if (isofile) free(isofile);
    if (esd) free(esd);
}

int LLVMFuzzerTestOneInput_254(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(u32) * 3) return 0;

    GF_ISOFile *isofile = create_dummy_isofile();
    GF_ESD *esd = create_dummy_esd();
    if (!isofile || !esd) {
        cleanup(isofile, esd);
        return 0;
    }

    u32 trackNumber = *((u32 *)Data);
    u32 sampleDescriptionIndex = *((u32 *)(Data + sizeof(u32)));
    u32 dummyValue = *((u32 *)(Data + 2 * sizeof(u32)));

    u32 outDescriptionIndex;
    u32 flags;
    u32 pcm_size;
    u32 width, height;

    // Fuzz gf_isom_new_mpeg4_description
    gf_isom_new_mpeg4_description(isofile, trackNumber, esd, NULL, NULL, &outDescriptionIndex);

    // Fuzz gf_isom_change_mpeg4_description
    gf_isom_change_mpeg4_description(isofile, trackNumber, sampleDescriptionIndex, esd);

    // Fuzz gf_isom_get_esd
    GF_ESD *retrieved_esd = gf_isom_get_esd(isofile, trackNumber, sampleDescriptionIndex);
    if (retrieved_esd) free(retrieved_esd);

    // Fuzz gf_isom_get_pcm_config
    gf_isom_get_pcm_config(isofile, trackNumber, sampleDescriptionIndex, &flags, &pcm_size);

    // Fuzz gf_isom_get_visual_info
    gf_isom_get_visual_info(isofile, trackNumber, sampleDescriptionIndex, &width, &height);

    // Fuzz gf_isom_add_track_to_root_od
    gf_isom_add_track_to_root_od(isofile, trackNumber);

    cleanup(isofile, esd);
    return 0;
}