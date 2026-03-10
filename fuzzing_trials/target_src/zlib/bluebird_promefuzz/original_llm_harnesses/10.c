// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit2_ at inflate.c:173:13 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// crc32 at crc32.c:945:15 in zlib.h
// crc32_combine at crc32.c:980:15 in zlib.h
// inflateReset at inflate.c:125:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

int LLVMFuzzerTestOneInput_10(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    memset(&strm, 0, sizeof(strm));

    // Initialize inflate with a random window size between 8 and 15
    int windowBits = 8 + (Data[0] % 8);
    if (inflateInit2_(&strm, windowBits, ZLIB_VERSION, sizeof(z_stream)) != Z_OK) {
        return 0;
    }

    // Set input data
    strm.next_in = (Bytef *)(Data + 1);
    strm.avail_in = Size - 1;

    // Prepare output buffer
    uint8_t out_buffer[1024];
    strm.next_out = out_buffer;
    strm.avail_out = sizeof(out_buffer);

    // Decompress the data
    int ret = inflate(&strm, Z_NO_FLUSH);
    if (ret != Z_STREAM_END && ret != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    // Calculate the actual output size
    size_t actual_out_size = sizeof(out_buffer) - strm.avail_out;

    // Combine CRC32 checksums
    uLong crc1 = crc32(0L, Z_NULL, 0);
    uLong crc2 = crc32(crc1, out_buffer, actual_out_size);
    crc32_combine(crc1, crc2, actual_out_size);

    // Reset the stream
    if (inflateReset(&strm) != Z_OK) {
        inflateEnd(&strm);
        return 0;
    }

    // Clean up
    inflateEnd(&strm);
    return 0;
}