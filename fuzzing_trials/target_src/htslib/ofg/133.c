#include <stdint.h>
#include <stddef.h>
#include "/src/htslib/htslib/hts.h"  // Include the correct path for the htslib header

int LLVMFuzzerTestOneInput_133(const uint8_t *data, size_t size) {
    // Call the function-under-test
    hts_md5_context *ctx = hts_md5_init();

    // Ensure the context is not NULL
    if (ctx != NULL) {
        // Feed the input data to the MD5 context
        hts_md5_update(ctx, data, size);

        // Clean up the context after use
        hts_md5_destroy(ctx);
    }

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

    LLVMFuzzerTestOneInput_133(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
