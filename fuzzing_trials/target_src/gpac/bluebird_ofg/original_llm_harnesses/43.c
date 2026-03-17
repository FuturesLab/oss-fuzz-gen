#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_43(const uint8_t *data, size_t size) {
    // Ensure there's enough data to extract meaningful values
    if (size < sizeof(u32) + sizeof(u64) + 1) {
        return 0;
    }

    // Initialize variables for function parameters
    GF_ISOFile *movie = gf_isom_open("dummy.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Extract trackNumber from the data
    u32 trackNumber = *(u32 *)data;
    data += sizeof(u32);
    size -= sizeof(u32);

    // Extract timestamp from the data
    u64 timestamp = *(u64 *)data;
    data += sizeof(u64);
    size -= sizeof(u64);

    // Create a name string from the remaining data
    char *name = (char *)malloc(size + 1);
    if (!name) {
        gf_isom_close(movie);
        return 0;
    }
    memcpy(name, data, size);
    name[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    gf_isom_add_chapter(movie, trackNumber, timestamp, name);

    // Clean up
    free(name);
    gf_isom_close(movie);

    return 0;
}