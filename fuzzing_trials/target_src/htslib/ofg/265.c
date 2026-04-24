#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/hts.h"  // Ensure this header is available and included

int LLVMFuzzerTestOneInput_265(const uint8_t *data, size_t size) {
    unsigned char digest[16];  // MD5 digest size is 16 bytes
    hts_md5_context *ctx;

    // Initialize the MD5 context
    ctx = hts_md5_init();
    if (ctx == NULL) {
        return 0;  // If initialization fails, exit early
    }

    // Update the MD5 context with the input data
    hts_md5_update(ctx, data, size);

    // Finalize the MD5 computation
    hts_md5_final(digest, ctx);

    // Free the MD5 context
    hts_md5_destroy(ctx);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_265(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
