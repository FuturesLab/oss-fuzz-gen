#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>
#include <string.h> // Include for memcpy

int LLVMFuzzerTestOneInput_36(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    GF_ISOOpenMode mode;

    // Ensure the input data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Create a null-terminated copy of the data
    char *null_terminated_data = (char *)malloc(size + 1);
    if (!null_terminated_data) {
        return 0; // Handle memory allocation failure
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0';

    // Initialize movie and mode with non-NULL values
    movie = gf_isom_open(null_terminated_data, GF_ISOM_OPEN_READ, NULL);
    mode = GF_ISOM_OPEN_READ;

    if (movie != NULL) {
        // Call the function-under-test
        gf_isom_can_access_movie(movie, mode);

        // Close the movie after testing
        gf_isom_close(movie);
    }

    // Free the allocated memory
    free(null_terminated_data);

    return 0;
}