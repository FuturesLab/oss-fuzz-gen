#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_14(const uint8_t *data, size_t size) {
    // Initialize the GF_ISOFile and GF_ISOSample structures
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure the size is large enough to extract a track number
    if (size < sizeof(uint32_t)) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract a track number from the data
    u32 trackNumber = *((u32*)data);
    data += sizeof(u32);
    size -= sizeof(u32);

    // Create a sample with some dummy data
    GF_ISOSample *sample = gf_isom_sample_new();
    if (!sample) {
        gf_isom_close(movie);
        return 0;
    }

    // Assign some data to the sample
    sample->dataLength = size;
    sample->data = (unsigned char *)malloc(size);
    if (sample->data) {
        memcpy(sample->data, data, size);
    }

    // Fuzz the function under test
    gf_isom_add_sample_shadow(movie, trackNumber, sample);

    // Clean up
    gf_isom_sample_del(&sample);
    gf_isom_close(movie);

    return 0;
}