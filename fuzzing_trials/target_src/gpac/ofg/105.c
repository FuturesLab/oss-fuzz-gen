#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_105(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    char *url_string;

    // Ensure the size is sufficient to create a valid string
    if (size < 1) {
        return 0;
    }

    // Initialize a movie object
    movie = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Allocate memory for the URL string and ensure it's null-terminated
    url_string = (char *)malloc(size + 1);
    if (url_string == NULL) {
        gf_isom_close(movie);
        return 0;
    }
    memcpy(url_string, data, size);
    url_string[size] = '\0';

    // Call the function under test
    gf_isom_set_root_od_url(movie, url_string);

    // Clean up
    free(url_string);
    gf_isom_close(movie);

    return 0;
}