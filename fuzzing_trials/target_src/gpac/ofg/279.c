#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_279(const uint8_t *data, size_t size) {
    // Ensure the data size is sufficient for extracting parameters
    if (size < sizeof(u32)) {
        return 0;
    }

    // Initialize parameters for the function-under-test
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    // Extract a trackNumber from the data
    u32 trackNumber = *((u32 *)data);

    // Ensure trackNumber is within a reasonable range
    trackNumber = trackNumber % 10 + 1;  // Assuming there are at least 10 tracks

    // Extract a Bool value from the data
    Bool remove = (data[sizeof(u32)] % 2) == 0;

    // Call the function-under-test
    gf_isom_update_aperture_info(movie, trackNumber, remove);

    // Clean up
    gf_isom_close(movie);

    return 0;
}