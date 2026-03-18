#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gpac/isomedia.h>
#include <gpac/constants.h>
#include <gpac/internal/isomedia_dev.h>  // Include this to ensure complete definition of GF_TextSample

int LLVMFuzzerTestOneInput_247(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract needed parameters
    if (size < 6) {
        return 0;
    }

    // Initialize GF_TextSample
    GF_TextSample samp;
    memset(&samp, 0, sizeof(GF_TextSample));

    // Extract start_char and end_char from the data
    u16 start_char = (u16)data[0] | ((u16)data[1] << 8);
    u16 end_char = (u16)data[2] | ((u16)data[3] << 8);

    // Extract URL and altString from the data
    // Ensure null-termination for the strings
    size_t url_length = (size - 4) / 2;
    size_t altString_length = (size - 4) - url_length;

    char *URL = (char *)malloc(url_length + 1);
    char *altString = (char *)malloc(altString_length + 1);

    if (!URL || !altString) {
        free(URL);
        free(altString);
        return 0;
    }

    memcpy(URL, data + 4, url_length);
    URL[url_length] = '\0';

    memcpy(altString, data + 4 + url_length, altString_length);
    altString[altString_length] = '\0';

    // Call the function-under-test
    gf_isom_text_add_hyperlink(&samp, URL, altString, start_char, end_char);

    // Clean up
    free(URL);
    free(altString);

    return 0;
}