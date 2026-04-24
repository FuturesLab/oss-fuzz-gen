#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_227(const uint8_t *data, size_t size) {
    // Initialize sam_hdr_t
    sam_hdr_t *hdr = sam_hdr_init();
    if (!hdr) {
        return 0; // If initialization fails, exit early
    }

    // Ensure size is sufficient for the strings
    if (size < 5) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Split the input data into parts for the function parameters
    size_t part_size = size / 5;
    const char *arg1 = (const char *)data;
    const char *arg2 = (const char *)(data + part_size);
    const char *arg3 = (const char *)(data + 2 * part_size);
    const char *arg4 = (const char *)(data + 3 * part_size);
    const char *arg5 = (const char *)(data + 4 * part_size);

    // Ensure null-termination for the strings
    char *null_terminated_arg1 = strndup(arg1, part_size);
    char *null_terminated_arg2 = strndup(arg2, part_size);
    char *null_terminated_arg3 = strndup(arg3, part_size);
    char *null_terminated_arg4 = strndup(arg4, part_size);
    char *null_terminated_arg5 = strndup(arg5, part_size);

    // Call the function-under-test
    sam_hdr_remove_tag_id(hdr, null_terminated_arg1, null_terminated_arg2, null_terminated_arg3, null_terminated_arg4);

    // Clean up
    free(null_terminated_arg1);
    free(null_terminated_arg2);
    free(null_terminated_arg3);
    free(null_terminated_arg4);
    free(null_terminated_arg5);
    sam_hdr_destroy(hdr);

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

    LLVMFuzzerTestOneInput_227(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
