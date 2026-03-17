#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "/src/gpac/include/gpac/isomedia.h"

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_WRITE_EDIT, NULL);
    if (movie == NULL) {
        return 0;
    }

    // Ensure the size is sufficient for threeCharCode and notice
    if (size < 4) {
        gf_isom_close(movie);
        return 0;
    }

    // Extract threeCharCode and notice from data
    char threeCharCode[4];
    memcpy(threeCharCode, data, 3);
    threeCharCode[3] = '\0';

    // The rest of the data is used for notice
    size_t noticeSize = size - 3;
    char *notice = (char *)malloc(noticeSize + 1);
    if (notice == NULL) {
        gf_isom_close(movie);
        return 0;
    }
    memcpy(notice, data + 3, noticeSize);
    notice[noticeSize] = '\0';

    // Call the function-under-test
    gf_isom_set_copyright(movie, threeCharCode, notice);

    // Clean up
    free(notice);
    gf_isom_close(movie);

    return 0;
}