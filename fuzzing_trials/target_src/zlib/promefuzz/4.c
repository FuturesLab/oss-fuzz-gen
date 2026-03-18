// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit2_ at inflate.c:173:13 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// deflateInit2_ at deflate.c:388:13 in zlib.h
// deflateSetDictionary at deflate.c:560:13 in zlib.h
// deflatePrime at deflate.c:746:13 in zlib.h
// deflateEnd at deflate.c:1294:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file != NULL) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_4(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize z_stream structures
    z_stream strm_inflate;
    z_stream strm_deflate;
    memset(&strm_inflate, 0, sizeof(z_stream));
    memset(&strm_deflate, 0, sizeof(z_stream));

    // Allocate output buffers
    Bytef out_buffer_inflate[1024];
    Bytef out_buffer_deflate[1024];

    // Initialize inflate
    int windowBits = 15;
    if (inflateInit2_(&strm_inflate, windowBits, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    // Compute crc32
    uLong crc = crc32(0L, Z_NULL, 0);
    crc = crc32(crc, Data, (uInt)Size);

    // Set input for inflate
    strm_inflate.next_in = (Bytef *)Data;
    strm_inflate.avail_in = (uInt)Size;
    strm_inflate.next_out = out_buffer_inflate;
    strm_inflate.avail_out = sizeof(out_buffer_inflate);

    // Perform inflate
    inflate(&strm_inflate, Z_NO_FLUSH);
    crc = crc32(crc, out_buffer_inflate, sizeof(out_buffer_inflate) - strm_inflate.avail_out);

    // End inflate
    inflateEnd(&strm_inflate);

    // Initialize deflate
    int level = Z_DEFAULT_COMPRESSION;
    int method = Z_DEFLATED;
    int memLevel = 8;
    int strategy = Z_DEFAULT_STRATEGY;
    if (deflateInit2_(&strm_deflate, level, method, windowBits, memLevel, strategy, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    // Set dictionary for deflate
    if (Size > 0) {
        deflateSetDictionary(&strm_deflate, Data, (uInt)Size);
    }

    // Prime deflate with some bits
    deflatePrime(&strm_deflate, 8, Data[0]);

    // Cleanup deflate
    deflateEnd(&strm_deflate);

    return 0;
}