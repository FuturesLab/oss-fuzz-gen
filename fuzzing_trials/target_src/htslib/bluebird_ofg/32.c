#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "htslib/sam.h" // Correct path for the header where bam_aux_update_array is declared

int LLVMFuzzerTestOneInput_32(const uint8_t *data, size_t size) {
    // Ensure the input size is sufficient to initialize all parameters
    if (size < sizeof(bam1_t) + 4 + sizeof(uint8_t) + sizeof(uint32_t)) {
        return 0;
    }

    // Initialize bam1_t structure
    bam1_t *b = (bam1_t *)malloc(sizeof(bam1_t));
    if (b == NULL) {
        return 0;
    }
    memset(b, 0, sizeof(bam1_t));

    // Initialize the tag as a 2-character string
    const char *tag = (const char *)(data + sizeof(bam1_t));
    
    // Ensure the tag is null-terminated
    char tag_buffer[3];
    memcpy(tag_buffer, tag, 2);
    tag_buffer[2] = '\0';
    
    // Initialize type
    uint8_t type = *(uint8_t *)(data + sizeof(bam1_t) + 2);

    // Initialize length
    uint32_t length = *(uint32_t *)(data + sizeof(bam1_t) + 3);

    // Ensure the array_data does not exceed the input size
    if (sizeof(bam1_t) + 3 + sizeof(uint32_t) + length > size) {
        free(b);
        return 0;
    }

    // Initialize data array
    void *array_data = (void *)(data + sizeof(bam1_t) + 3 + sizeof(uint32_t));

    // Call the function-under-test
    int result = bam_aux_update_array(b, tag_buffer, type, length, array_data);

    // Clean up
    free(b);

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

    LLVMFuzzerTestOneInput_32(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
