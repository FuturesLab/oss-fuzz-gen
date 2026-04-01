#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_285(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1;
    GF_DIMSDescription desc;
    char URLname[256];
    char URNname[256];
    u32 outDescriptionIndex;

    // Ensure movie is not NULL
    if (!movie) {
        return 0;
    }

    // Initialize URLname and URNname with data
    if (size > 0) {
        size_t copy_size = size < 255 ? size : 255;
        memcpy(URLname, data, copy_size);
        URLname[copy_size] = '\0';

        memcpy(URNname, data, copy_size);
        URNname[copy_size] = '\0';
    } else {
        strcpy(URLname, "default_url");
        strcpy(URNname, "default_urn");
    }

    // Call the function-under-test
    gf_isom_new_dims_description(movie, trackNumber, &desc, URLname, URNname, &outDescriptionIndex);

    // Clean up
    gf_isom_close(movie);

    return 0;
}