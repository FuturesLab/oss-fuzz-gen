#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>  // Assuming the header file is part of the htslib library

int LLVMFuzzerTestOneInput_92(const uint8_t *data, size_t size) {
    // Initialize the context using the correct function call
    hts_md5_context *ctx = hts_md5_init();
    if (ctx == NULL) {
        return 0;
    }

    // Call the function-under-test
    hts_md5_update(ctx, (const void *)data, (unsigned long)size);

    // Cleanup
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

    LLVMFuzzerTestOneInput_92(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
