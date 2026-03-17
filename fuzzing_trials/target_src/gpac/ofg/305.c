#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_305(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1; // Example track number
    u32 StreamDescriptionIndex = 1; // Example stream description index

    // Ensure the data size is sufficient for creating a sample
    if (size < sizeof(GF_ISOSample)) {
        return 0;
    }

    // Allocate memory for the sample
    GF_ISOSample *sample = (GF_ISOSample *)malloc(sizeof(GF_ISOSample));
    if (!sample) {
        return 0;
    }

    // Initialize sample with data
    sample->data = (u8 *)data; // Corrected pointer type
    sample->dataLength = size;
    sample->DTS = 0; // Example decoding timestamp
    sample->CTS_Offset = 0; // Example composition time offset
    sample->IsRAP = 1; // Example random access point flag
    sample->duration = 1000; // Corrected member name for duration

    // Call the function-under-test
    gf_isom_add_sample(movie, trackNumber, StreamDescriptionIndex, sample);

    // Clean up
    free(sample);
    gf_isom_close(movie);

    return 0;
}