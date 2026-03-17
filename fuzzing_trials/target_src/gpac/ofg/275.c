#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_275(const uint8_t *data, size_t size) {
    // Initialize variables
    GF_ISOFile *the_file = gf_isom_open(NULL, GF_ISOM_OPEN_WRITE, NULL);
    u32 trackNumber = 1;
    u32 StreamDescriptionIndex = 1;
    char *codec_params = NULL;

    // Ensure the data is large enough to use for codec_params
    if (size > 0) {
        // Allocate memory for codec_params and copy data into it
        codec_params = (char *)malloc(size + 1);
        if (codec_params == NULL) {
            gf_isom_close(the_file);
            return 0;
        }
        memcpy(codec_params, data, size);
        codec_params[size] = '\0'; // Null-terminate the string
    } else {
        // Provide a default non-NULL value if size is 0
        codec_params = strdup("default_codec_params");
    }

    // Call the function-under-test
    gf_isom_subtitle_set_mime(the_file, trackNumber, StreamDescriptionIndex, codec_params);

    // Clean up
    free(codec_params);
    gf_isom_close(the_file);

    return 0;
}