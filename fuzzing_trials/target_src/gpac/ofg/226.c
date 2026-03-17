#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpac/isomedia.h"

int LLVMFuzzerTestOneInput_226(const uint8_t *data, size_t size) {
    // Initialize the_file
    GF_ISOFile *the_file = gf_isom_open("temp.mp4", GF_ISOM_OPEN_WRITE, NULL);
    if (!the_file) {
        return 0;
    }

    // Ensure size is sufficient for trackNumber and text
    if (size < sizeof(uint32_t) + 1) {
        gf_isom_close(the_file);
        return 0;
    }

    // Extract trackNumber from data
    u32 trackNumber = *(const u32 *)data;

    // Extract text from data
    const char *text = (const char *)(data + sizeof(uint32_t));

    // Ensure text is null-terminated
    size_t text_length = size - sizeof(uint32_t);
    char *text_buffer = (char *)malloc(text_length + 1);
    if (!text_buffer) {
        gf_isom_close(the_file);
        return 0;
    }
    memcpy(text_buffer, text, text_length);
    text_buffer[text_length] = '\0';

    // Call the function-under-test
    gf_isom_sdp_add_track_line(the_file, trackNumber, text_buffer);

    // Clean up
    free(text_buffer);
    gf_isom_close(the_file);

    return 0;
}