#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "htslib/sam.h" // Correct path for sam.h

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    // Ensure the size is sufficient to create a non-NULL string
    if (size < 1) return 0;

    // Initialize sam_hdr_t object
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) return 0; // Exit if initialization fails

    // Allocate memory for a string and ensure it's null-terminated
    char *pg_string = (char *)malloc(size + 1);
    if (pg_string == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(pg_string, data, size);
    pg_string[size] = '\0'; // Null-terminate the string

    // Call the function-under-test
    sam_hdr_add_pg(hdr, pg_string, NULL);

    // Clean up
    free(pg_string);
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

    LLVMFuzzerTestOneInput_132(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
