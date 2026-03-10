#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "zlib.h"

#define CHUNK 256

static unsigned int dummy_in_func(void FAR *in_desc, z_const unsigned char FAR **buf) {
    size_t *remaining = (size_t *)in_desc;
    *buf = (z_const unsigned char FAR *)(remaining + 1);
    unsigned int to_read = (*remaining < CHUNK) ? (unsigned int)(*remaining) : CHUNK;
    *remaining -= to_read;
    return to_read;
}

static int dummy_out_func(void FAR *out_desc, unsigned char FAR *buf, unsigned len) {
    unsigned char *output_buffer = (unsigned char *)out_desc;
    if (output_buffer) {
        memcpy(output_buffer, buf, len);
    }
    return 0;
}

int LLVMFuzzerTestOneInput_17(const uint8_t *Data, size_t Size) {
    if (Size < 1) {
        return 0;
    }

    z_stream strm;
    unsigned char out[CHUNK];
    int ret;

    // inflateInit2_
    memset(&strm, 0, sizeof(z_stream));
    ret = inflateInit2_(&strm, 15, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) {
        return 0;
    }

    // Set up input
    strm.next_in = (Bytef *)Data;
    strm.avail_in = Size;

    // Set up output
    strm.next_out = out;
    strm.avail_out = CHUNK;

    // inflate
    do {

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of inflate
        ret = inflate(&strm, Size);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


        if (ret == Z_STREAM_ERROR) {
                break;
        }
        if (ret == Z_MEM_ERROR || ret == Z_DATA_ERROR || ret == Z_BUF_ERROR) {
                break;
        }
        if (strm.avail_out == 0) {
            strm.next_out = out;
            strm.avail_out = CHUNK;
        }
    } while (ret != Z_STREAM_END);

    // inflateEnd
    inflateEnd(&strm);

    // inflateBackInit_
    unsigned char window[CHUNK];
    ret = inflateBackInit_(&strm, 15, window, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) {
        return 0;
    }

    // Prepare data for inflateBack
    size_t remaining = Size;
    size_t *input_desc = malloc(Size + sizeof(size_t));
    if (!input_desc) {
        return 0;
    }
    *input_desc = remaining;
    memcpy(input_desc + 1, Data, Size);

    // Allocate output buffer for inflateBack
    unsigned char *back_output = malloc(CHUNK);
    if (!back_output) {
        free(input_desc);
        return 0;
    }

    // inflateBack
    ret = inflateBack(&strm, dummy_in_func, input_desc, dummy_out_func, back_output);

    // inflateBackEnd
    inflateBackEnd(&strm);

    free(input_desc);
    free(back_output);

    return 0;
}