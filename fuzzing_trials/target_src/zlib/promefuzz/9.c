// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateInit2_ at inflate.c:173:13 in zlib.h
// inflateGetHeader at inflate.c:1219:13 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// inflateSetDictionary at inflate.c:1187:13 in zlib.h
// inflateSetDictionary at inflate.c:1187:13 in zlib.h
// inflateSetDictionary at inflate.c:1187:13 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// inflateCopy at inflate.c:1328:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// inflateReset2 at inflate.c:136:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
// inflateEnd at inflate.c:1155:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "zlib.h"

static void write_dummy_file(const uint8_t *data, size_t size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(data, 1, size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    z_stream strm;
    gz_header header;
    z_stream strm_copy;
    Bytef dictionary[32] = {0};  // Dummy dictionary
    Bytef output[256] = {0};     // Output buffer

    memset(&strm_copy, 0, sizeof(z_stream));

    // Initialize z_stream
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.next_in = (Bytef *)Data;
    strm.avail_in = (uInt)Size;
    strm.next_out = output;
    strm.avail_out = sizeof(output);

    // Initialize inflate with a random window size
    int ret = inflateInit2_(&strm, (int)(Data[0] % 16) + 8, ZLIB_VERSION, sizeof(z_stream));
    if (ret != Z_OK) return 0;

    // Get header
    ret = inflateGetHeader(&strm, &header);
    if (ret != Z_OK) goto cleanup;

    // Inflate
    ret = inflate(&strm, Z_NO_FLUSH);
    if (ret != Z_OK && ret != Z_STREAM_END) goto cleanup;

    // Set Dictionary multiple times
    ret = inflateSetDictionary(&strm, dictionary, sizeof(dictionary));
    if (ret != Z_OK) goto cleanup;

    ret = inflateSetDictionary(&strm, dictionary, sizeof(dictionary));
    if (ret != Z_OK) goto cleanup;

    ret = inflateSetDictionary(&strm, dictionary, sizeof(dictionary));
    if (ret != Z_OK) goto cleanup;

    // Inflate again
    ret = inflate(&strm, Z_FINISH);
    if (ret != Z_OK && ret != Z_STREAM_END) goto cleanup;

    // Copy stream
    ret = inflateCopy(&strm_copy, &strm);
    if (ret != Z_OK) goto cleanup;

    // End and reset
    ret = inflateEnd(&strm);
    if (ret != Z_OK) return 0;

    ret = inflateReset2(&strm, (int)(Data[0] % 16) + 8);
    if (ret != Z_OK) goto cleanup;

cleanup:
    inflateEnd(&strm);
    if (strm_copy.state != NULL) {
        inflateEnd(&strm_copy);
    }

    return 0;
}