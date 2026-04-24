#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_109(const uint8_t *data, size_t size) {
    // Ensure the data is large enough to be split into meaningful parts
    if (size < 4) {
        return 0;
    }

    // Initialize a sam_hdr_t structure
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) {
        return 0;
    }

    // Split the input data into parts for the function parameters
    size_t part_size = size / 4;
    const char *arg1 = (const char *)data;
    const char *arg2 = (const char *)(data + part_size);
    const char *arg3 = (const char *)(data + 2 * part_size);
    const char *arg4 = (const char *)(data + 3 * part_size);

    // Null-terminate the strings
    char *arg1_str = (char *)malloc(part_size + 1);
    char *arg2_str = (char *)malloc(part_size + 1);
    char *arg3_str = (char *)malloc(part_size + 1);
    char *arg4_str = (char *)malloc(part_size + 1);

    if (!arg1_str || !arg2_str || !arg3_str || !arg4_str) {
        sam_hdr_destroy(hdr);
        free(arg1_str);
        free(arg2_str);
        free(arg3_str);
        free(arg4_str);
        return 0;
    }

    memcpy(arg1_str, arg1, part_size);
    memcpy(arg2_str, arg2, part_size);
    memcpy(arg3_str, arg3, part_size);
    memcpy(arg4_str, arg4, part_size);

    arg1_str[part_size] = '\0';
    arg2_str[part_size] = '\0';
    arg3_str[part_size] = '\0';
    arg4_str[part_size] = '\0';

    // Call the function-under-test
    sam_hdr_remove_except(hdr, arg1_str, arg2_str, arg3_str);

    // Clean up
    sam_hdr_destroy(hdr);
    free(arg1_str);
    free(arg2_str);
    free(arg3_str);
    free(arg4_str);

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

    LLVMFuzzerTestOneInput_109(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
