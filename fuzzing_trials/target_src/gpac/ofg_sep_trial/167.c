#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_167(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Ensure the URL string is null-terminated and not too long
    size_t url_length = size < 256 ? size : 255;
    char *url_string = (char *)malloc(url_length + 1);
    if (url_string == NULL) {
        gf_isom_close(movie);
        return 0;
    }
    memcpy(url_string, data, url_length);
    url_string[url_length] = '\0';

    // Call the function-under-test
    gf_isom_set_root_od_url(movie, url_string);

    // Clean up
    free(url_string);
    gf_isom_close(movie);

    return 0;
}