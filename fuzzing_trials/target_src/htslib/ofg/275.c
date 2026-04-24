#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>
#include <htslib/hts_defs.h>
#include "/src/htslib/hts_internal.h"

int LLVMFuzzerTestOneInput_275(const uint8_t *data, size_t size) {
    if (size < sizeof(int) * 4 + sizeof(uint64_t)) {
        return 0;
    }

    // Extract integers and uint64_t from the input data
    int arg1 = *(int *)(data);
    int arg2 = *(int *)(data + sizeof(int));
    uint64_t arg3 = *(uint64_t *)(data + sizeof(int) * 2);
    int arg4 = *(int *)(data + sizeof(int) * 2 + sizeof(uint64_t));
    int arg5 = *(int *)(data + sizeof(int) * 3 + sizeof(uint64_t));

    // Call the function-under-test
    hts_idx_t *index = hts_idx_init(arg1, arg2, arg3, arg4, arg5);

    // Clean up if necessary
    if (index != NULL) {
        hts_idx_destroy(index);
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

    LLVMFuzzerTestOneInput_275(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
