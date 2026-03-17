#include <stdint.h>
#include <stddef.h>
#include <gpac/isomedia.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_121(const uint8_t *data, size_t size) {
    GF_ISOFile *movie;
    GF_ISOStorageMode storageMode;

    if (size < sizeof(GF_ISOStorageMode)) {
        return 0;
    }

    // Initialize a GF_ISOFile object using a different approach
    movie = gf_isom_open(NULL, GF_ISOM_OPEN_READ, NULL);
    if (!movie) {
        return 0;
    }

    // Extract storageMode from the input data
    storageMode = *(GF_ISOStorageMode *)(data + (size - sizeof(GF_ISOStorageMode)));

    // Call the function under test
    gf_isom_set_storage_mode(movie, storageMode);

    // Cleanup
    gf_isom_close(movie);

    return 0;
}

#ifdef __cplusplus
}
#endif