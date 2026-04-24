#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < 2) {
        return 0;
    }

    // Initialize a sam_hdr_t object
    sam_hdr_t *hdr = sam_hdr_init();
    if (hdr == NULL) {
        return 0;
    }

    // Use some of the input data to create a dummy header text
    // Ensure the header text is null-terminated
    size_t header_size = size / 2;
    char *header_text = (char *)malloc(header_size + 1);
    if (header_text == NULL) {
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(header_text, data, header_size);
    header_text[header_size] = '\0';

    // Add the header text to the sam_hdr_t object
    if (sam_hdr_add_lines(hdr, header_text, header_size) < 0) {
        free(header_text);
        sam_hdr_destroy(hdr);
        return 0;
    }

    // Use the remaining data as the program ID string
    size_t pg_id_size = size - header_size;
    char *pg_id = (char *)malloc(pg_id_size + 1);
    if (pg_id == NULL) {
        free(header_text);
        sam_hdr_destroy(hdr);
        return 0;
    }
    memcpy(pg_id, data + header_size, pg_id_size);
    pg_id[pg_id_size] = '\0';

    // Call the function-under-test
    const char *result = sam_hdr_pg_id(hdr, pg_id);

    // Clean up
    free(header_text);
    free(pg_id);
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

    LLVMFuzzerTestOneInput_188(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
