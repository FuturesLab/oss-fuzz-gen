#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

#define THREE_CHAR_CODE_SIZE 4

int LLVMFuzzerTestOneInput_265(const uint8_t *data, size_t size) {
    // Ensure that the input size is sufficient for the threeCharCode and notice
    if (size < THREE_CHAR_CODE_SIZE + 1) {
        return 0;
    }

    // Initialize GF_ISOFile structure
    GF_ISOFile *movie = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!movie) {
        return 0;
    }

    // Allocate and copy threeCharCode
    char threeCharCode[THREE_CHAR_CODE_SIZE];
    memcpy(threeCharCode, data, THREE_CHAR_CODE_SIZE - 1);
    threeCharCode[THREE_CHAR_CODE_SIZE - 1] = '\0'; // Null-terminate

    // Allocate and copy notice
    size_t notice_size = size - (THREE_CHAR_CODE_SIZE - 1);
    char *notice = (char *)malloc(notice_size + 1);
    if (!notice) {
        gf_isom_close(movie);
        return 0;
    }
    memcpy(notice, data + (THREE_CHAR_CODE_SIZE - 1), notice_size);
    notice[notice_size] = '\0'; // Null-terminate

    // Call the function-under-test
    gf_isom_set_copyright(movie, threeCharCode, notice);

    // Clean up
    free(notice);
    gf_isom_close(movie);

    return 0;
}