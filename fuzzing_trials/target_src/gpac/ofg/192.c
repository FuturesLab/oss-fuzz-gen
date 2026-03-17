#include <stdint.h>
#include <stdlib.h>
#include <string.h>  // Include this header for memory functions
#include <gpac/isomedia.h>
#include <gpac/tools.h>  // Include this header for Bool type and related definitions

int LLVMFuzzerTestOneInput_192(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to prevent buffer overflow
    char *null_terminated_data = (char *)malloc(size + 1);
    if (!null_terminated_data) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(null_terminated_data, data, size);
    null_terminated_data[size] = '\0'; // Null-terminate the data

    // Initialize a GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open(null_terminated_data, GF_ISOM_OPEN_READ, NULL);
    if (movie == NULL) {
        free(null_terminated_data); // Free allocated memory before exiting
        return 0; // If opening fails, exit early
    }

    // Initialize a Bool variable for reset_tables
    Bool reset_tables = (size % 2 == 0) ? GF_TRUE : GF_FALSE;

    // Call the function-under-test
    gf_isom_release_segment(movie, reset_tables);

    // Close the movie file to clean up
    gf_isom_close(movie);

    // Free the allocated memory
    free(null_terminated_data);

    return 0;
}