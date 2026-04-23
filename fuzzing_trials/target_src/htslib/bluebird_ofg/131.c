#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "htslib/sam.h" // Correct path for sam.h

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    // Declare and initialize the sam_hdr_t pointer
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Ensure the input size is sufficient to extract meaningful strings
    if (size < 4) {
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Extract strings from the fuzzer input data
    const char *type = (const char *)data;
    const char *id = (const char *)(data + 1);
    const char *key = (const char *)(data + 2);
    const char *value = (const char *)(data + 3);

    // Call the function-under-test
    int result = sam_hdr_remove_tag_id(hdr, type, id, key, value);

    // Clean up
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

    if(size < 1 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_131(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
