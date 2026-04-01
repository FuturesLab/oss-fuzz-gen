// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit2_ at inflate.c:173:13 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// deflateInit2_ at deflate.c:388:13 in zlib.h
// deflateSetDictionary at deflate.c:560:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflatePrime at deflate.c:746:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_12(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize z_stream for inflate
    z_stream inflate_stream;
    memset(&inflate_stream, 0, sizeof(inflate_stream));

    // Initialize z_stream for deflate
    z_stream deflate_stream;
    memset(&deflate_stream, 0, sizeof(deflate_stream));

    // Prepare input and output buffers
    Bytef out_buffer[1024];
    inflate_stream.next_in = Data;
    inflate_stream.avail_in = Size;
    inflate_stream.next_out = out_buffer;
    inflate_stream.avail_out = sizeof(out_buffer);

    deflate_stream.next_in = Data;
    deflate_stream.avail_in = Size;
    deflate_stream.next_out = out_buffer;
    deflate_stream.avail_out = sizeof(out_buffer);

    // InflateInit2_
    if (inflateInit2_(&inflate_stream, 15 + 32, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    // First crc32 calculation
    uLong crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, Data, Size);

    // Inflate
    int ret = inflate(&inflate_stream, Z_NO_FLUSH);
    if (ret != Z_STREAM_END && ret != Z_OK) {
        inflateEnd(&inflate_stream);
        return 0;
    }

    // Second crc32 calculation
    crc = crc32(crc, out_buffer, sizeof(out_buffer) - inflate_stream.avail_out);

    // Cleanup inflate
    inflateEnd(&inflate_stream);

    // DeflateInit2_
    if (deflateInit2_(&deflate_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15, 8, Z_DEFAULT_STRATEGY, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    // DeflateSetDictionary
    if (deflateSetDictionary(&deflate_stream, Data, Size > 1024 ? 1024 : Size) != Z_OK) {
        deflateEnd(&deflate_stream);
        return 0;
    }

    // DeflatePrime
    if (deflatePrime(&deflate_stream, 1, 1) != Z_OK) {
        deflateEnd(&deflate_stream);
        return 0;
    }

    // Cleanup deflate
    deflateEnd(&deflate_stream);

    // Write to dummy file
    write_dummy_file(Data, Size);

    return 0;
}