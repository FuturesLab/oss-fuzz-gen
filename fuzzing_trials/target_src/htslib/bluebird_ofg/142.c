#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_142(const uint8_t *data, size_t size) {
    // Ensure there's enough data to work with
    if (size < 3) {
        return 0;
    }

    // Create a dummy sam_hdr_t object
    sam_hdr_t *header = sam_hdr_init();
    if (header == NULL) {
        return 0;
    }

    // Allocate memory for the strings, ensuring they are null-terminated
    char *type = (char *)malloc(2);
    char *id = (char *)malloc(2);

    if (type == NULL || id == NULL) {
        sam_hdr_destroy(header);
        free(type);
        free(id);
        return 0;
    }

    // Initialize the strings with data from the input
    strncpy(type, (const char *)data, 1);
    type[1] = '\0';
    strncpy(id, (const char *)(data + 1), 1);
    id[1] = '\0';

    // The 'iter' parameter is a void pointer, we can pass NULL for testing
    void *iter = NULL;

    // Call the function-under-test
    sam_hdr_remove_lines(header, type, id, iter);

    // Clean up
    sam_hdr_destroy(header);
    free(type);
    free(id);

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

    LLVMFuzzerTestOneInput_142(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
