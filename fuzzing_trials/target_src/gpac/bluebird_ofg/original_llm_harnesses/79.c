#include <stdint.h>
#include <stdlib.h>
#include <string.h> // For memcpy
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_79(const uint8_t *data, size_t size) {
    // Ensure that we have enough data for the GF_DOVIDecoderConfigurationRecord
    if (size < sizeof(GF_DOVIDecoderConfigurationRecord)) {
        return 0;
    }

    // Create a new ISO file, providing a temporary directory for file operations
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, "/tmp");
    if (!movie) {
        return 0;
    }

    // Allocate memory for GF_DOVIDecoderConfigurationRecord
    GF_DOVIDecoderConfigurationRecord *dvcc = (GF_DOVIDecoderConfigurationRecord *)malloc(sizeof(GF_DOVIDecoderConfigurationRecord));
    if (!dvcc) {
        gf_isom_close(movie);
        return 0;
    }

    // Initialize dvcc with data
    memcpy(dvcc, data, sizeof(GF_DOVIDecoderConfigurationRecord));

    // Ensure trackNumber and StreamDescriptionIndex are within valid range
    u32 trackNumber = 1;
    u32 StreamDescriptionIndex = 1;

    // Call the function-under-test
    gf_isom_set_dolby_vision_profile(movie, trackNumber, StreamDescriptionIndex, dvcc);

    // Free allocated memory
    free(dvcc);
    gf_isom_close(movie);

    return 0;
}