#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_104(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure the URL string is null-terminated
    char *url_string = (char *)malloc(size + 1);
    if (!url_string) {
        gf_isom_close(movie);
        return 0;
    }
    memcpy(url_string, data, size);
    url_string[size] = '\0';

    // Call the function-under-test
    gf_isom_set_root_od_url(movie, url_string);

    // Clean up
    free(url_string);
    gf_isom_close(movie);

    return 0;
}