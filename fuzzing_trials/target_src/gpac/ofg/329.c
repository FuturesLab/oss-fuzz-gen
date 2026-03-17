#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_329(const uint8_t *data, size_t size) {
    // Define a minimum size requirement based on the expected input structure
    size_t min_size = sizeof(u32) * 2 + sizeof(GF_DOVIDecoderConfigurationRecord);
    
    // Check if the size is sufficient to initialize all parameters
    if (size < min_size) {
        return 0;
    }

    // Initialize trackNumber and StreamDescriptionIndex
    u32 trackNumber = *(u32 *)(data);
    u32 StreamDescriptionIndex = *(u32 *)(data + sizeof(u32));

    // Initialize GF_DOVIDecoderConfigurationRecord
    GF_DOVIDecoderConfigurationRecord *dvcc = (GF_DOVIDecoderConfigurationRecord *)(data + sizeof(u32) * 2);

    // Create a dummy GF_ISOFile pointer as we cannot determine its size
    GF_ISOFile *movie = NULL;

    // Call the function-under-test
    gf_isom_set_dolby_vision_profile(movie, trackNumber, StreamDescriptionIndex, dvcc);

    return 0;
}