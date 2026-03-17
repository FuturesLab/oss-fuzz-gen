#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_315(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *movie;
    u32 trackNumber;
    u64 timestamp;
    char *name;

    // Ensure size is sufficient for extracting necessary data
    if (size < sizeof(trackNumber) + sizeof(timestamp) + 1) {
        return 0;
    }

    // Initialize the movie (assuming a function to create a movie exists)
    movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract trackNumber and timestamp from the input data
    memcpy(&trackNumber, data, sizeof(trackNumber));
    memcpy(&timestamp, data + sizeof(trackNumber), sizeof(timestamp));

    // Allocate memory for name and copy data into it
    size_t name_length = size - sizeof(trackNumber) - sizeof(timestamp);
    name = (char *)malloc(name_length + 1);
    if (!name) {
        gf_isom_close(movie);
        return 0;
    }
    memcpy(name, data + sizeof(trackNumber) + sizeof(timestamp), name_length);
    name[name_length] = '\0';  // Ensure null-termination

    // Call the function-under-test
    gf_isom_add_chapter(movie, trackNumber, timestamp, name);

    // Clean up
    free(name);
    gf_isom_close(movie);

    return 0;
}