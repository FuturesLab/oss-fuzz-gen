#include <stdint.h>
#include <stdlib.h>
#include <gpac/isomedia.h>
#include "/src/gpac/src/isomedia/movie_fragments.c"

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_215(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;

    // Initialize the GF_ISOFile structure
    file = gf_isom_open_file("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);

    if (file == NULL) {
        return 0;
    }

    // Call the function-under-test
    gf_isom_enable_mfra(file);

    // Cleanup
    gf_isom_close(file); // Corrected function name

    return 0;
}

#ifdef __cplusplus
}
#endif