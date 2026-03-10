// This fuzz driver is generated for library zlib, aiming to fuzz the following functions:
// inflateUndermine at inflate.c:1370:13 in zlib.h
// inflateCopy at inflate.c:1328:13 in zlib.h
// inflateBack at infback.c:191:13 in zlib.h
// inflateCodesUsed at inflate.c:1408:23 in zlib.h
// inflate at inflate.c:474:13 in zlib.h
// inflateBackEnd at infback.c:574:13 in zlib.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

static unsigned int dummy_in_func(void *desc, unsigned char **buffer) {
    *buffer = (unsigned char *)desc;
    return *(size_t *)desc;
}

static int dummy_out_func(void *desc, unsigned char *buffer, unsigned len) {
    (void)desc;
    (void)buffer;
    return len;
}

int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(z_stream)) {
        return 0;
    }

    z_stream strm;
    memset(&strm, 0, sizeof(z_stream));

    // Allocate input and output buffers
    unsigned char *input = malloc(Size);
    unsigned char *output = malloc(Size);
    if (!input || !output) {
        free(input);
        free(output);
        return 0;
    }

    memcpy(input, Data, Size);
    strm.next_in = input;
    strm.avail_in = Size;
    strm.next_out = output;
    strm.avail_out = Size;

    // Fuzz inflateUndermine
    int subvert = Data[0] % 2;
    inflateUndermine(&strm, subvert);

    // Fuzz inflateCopy
    z_stream dest;
    memset(&dest, 0, sizeof(z_stream));
    inflateCopy(&dest, &strm);

    // Fuzz inflateBack
    inflateBack(&strm, dummy_in_func, &Size, dummy_out_func, NULL);

    // Fuzz inflateCodesUsed
    inflateCodesUsed(&strm);

    // Fuzz inflate
    int flush = Z_NO_FLUSH;
    inflate(&strm, flush);

    // Fuzz inflateBackEnd
    inflateBackEnd(&strm);

    // Cleanup
    free(input);
    free(output);
    return 0;
}