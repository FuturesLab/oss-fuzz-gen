#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    if (size < sizeof(uint32_t) + 4 * sizeof(uint64_t) + sizeof(GF_ISOEditType)) {
        gf_isom_close(movie);
        return 0;
    }

    uint32_t trackNumber = *((uint32_t *)data);
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    uint64_t EditTime = *((uint64_t *)data);
    data += sizeof(uint64_t);
    size -= sizeof(uint64_t);

    uint64_t EditDuration = *((uint64_t *)data);
    data += sizeof(uint64_t);
    size -= sizeof(uint64_t);

    uint64_t MediaTime = *((uint64_t *)data);
    data += sizeof(uint64_t);
    size -= sizeof(uint64_t);

    GF_ISOEditType EditMode = *((GF_ISOEditType *)data);

    gf_isom_set_edit(movie, trackNumber, EditTime, EditDuration, MediaTime, EditMode);

    gf_isom_close(movie);

    return 0;
}