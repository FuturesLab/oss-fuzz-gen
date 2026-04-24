#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <htslib/hts.h>
#include <htslib/hts_defs.h>
#include "/src/htslib/htslib/hts.h" // Correct include for hts_idx functions

int LLVMFuzzerTestOneInput_29(const uint8_t *data, size_t size) {
    if (size < sizeof(int) + 2 * sizeof(hts_pos_t) + sizeof(uint64_t) + sizeof(int)) {
        return 0;
    }

    // Initialize parameters for hts_idx_push
    int int_param1 = *(int *)data;
    data += sizeof(int);
    size -= sizeof(int);

    hts_pos_t hts_pos_param1 = *(hts_pos_t *)data;
    data += sizeof(hts_pos_t);
    size -= sizeof(hts_pos_t);

    hts_pos_t hts_pos_param2 = *(hts_pos_t *)data;
    data += sizeof(hts_pos_t);
    size -= sizeof(hts_pos_t);

    uint64_t uint64_param = *(uint64_t *)data;
    data += sizeof(uint64_t);
    size -= sizeof(uint64_t);

    int int_param2 = *(int *)data;

    // Create a dummy hts_idx_t object
    hts_idx_t *idx = hts_idx_init(0, HTS_FMT_CSI, 0, 0, 0);

    if (idx == NULL) {
        return 0;
    }

    // Call the function under test
    hts_idx_push(idx, int_param1, hts_pos_param1, hts_pos_param2, uint64_param, int_param2);

    // Clean up
    hts_idx_destroy(idx);

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

    LLVMFuzzerTestOneInput_29(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
