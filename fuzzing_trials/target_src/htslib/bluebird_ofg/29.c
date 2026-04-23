#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/hts.h" // Assuming the library provides the hts_md5_context definition

// Remove the 'extern "C"' linkage specification as it is not valid in C code
int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    unsigned char md5_result[16]; // MD5 results are typically 16 bytes
    hts_md5_context *ctx;

    // Initialize the MD5 context
    ctx = hts_md5_init();
    if (ctx == NULL) {
        return 0; // Exit if context initialization fails
    }

    // Update the MD5 context with the input data
    hts_md5_update(ctx, data, size);

    // Finalize the MD5 computation
    hts_md5_final(md5_result, ctx);

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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_29(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
