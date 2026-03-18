// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit2_ at inflate.c:173:13 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// inflateBackInit_ at infback.c:25:13 in zlib.h
// inflateBack at infback.c:191:13 in zlib.h
// inflateBackEnd at infback.c:574:13 in zlib.h
// inflateBackEnd at infback.c:574:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

#define CHUNK 256

typedef struct {
    const unsigned char *data;
    size_t size;
    size_t offset;
} InputDesc;

static int dummy_in_func(void *desc, unsigned char **buffer) {
    InputDesc *input = (InputDesc *)desc;
    if (input->offset >= input->size) {
        return 0;
    }
    *buffer = (unsigned char *)&input->data[input->offset];
    int available = input->size - input->offset;
    input->offset = input->size; // Move offset to end
    return available;
}

static int dummy_out_func(void *desc, unsigned char *buffer, unsigned len) {
    (void)desc; // Unused
    (void)buffer; // Unused
    return len;
}

int LLVMFuzzerTestOneInput_6(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    int ret = inflateInit2_(&strm, 15, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) return 0;

    unsigned char out[CHUNK];
    strm.avail_in = Size;
    strm.next_in = (z_const Bytef *)Data;
    strm.avail_out = CHUNK;
    strm.next_out = out;

    // Inflate loop
    while (strm.avail_in > 0) {
        ret = inflate(&strm, Z_NO_FLUSH);
        if (ret == Z_STREAM_END) break;
        if (ret != Z_OK) {
            inflateEnd(&strm);
            return 0;
        }
    }

    inflateEnd(&strm);

    // InflateBackInit
    unsigned char window[CHUNK];
    ret = inflateBackInit_(&strm, 15, window, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) return 0;

    // Prepare input descriptor
    InputDesc inputDesc = { Data, Size, 0 };

    // InflateBack
    ret = inflateBack(&strm, dummy_in_func, &inputDesc, dummy_out_func, NULL);
    if (ret != Z_OK && ret != Z_STREAM_END) {
        inflateBackEnd(&strm);
        return 0;
    }

    // Clean up
    inflateBackEnd(&strm);

    return 0;
}