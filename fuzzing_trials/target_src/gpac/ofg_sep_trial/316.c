#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_316(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Ensure size is large enough to extract meaningful data
    if (size < sizeof(uint32_t) + sizeof(uint64_t) + 1) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract trackNumber from the data
    uint32_t trackNumber = *(uint32_t *)data;
    data += sizeof(uint32_t);
    size -= sizeof(uint32_t);

    // Extract timestamp from the data
    uint64_t timestamp = *(uint64_t *)data;
    data += sizeof(uint64_t);
    size -= sizeof(uint64_t);

    // Extract name from the remaining data
    char *name = (char *)malloc(size + 1);
    if (!name) {
        gf_isom_close(movie);
        return 0;
    }
    memcpy(name, data, size);
    name[size] = '\0'; // Null-terminate the string

    // Call the function under test
    gf_isom_add_chapter(movie, trackNumber, timestamp, name);

    // Clean up
    free(name);
    gf_isom_close(movie);

    return 0;
}