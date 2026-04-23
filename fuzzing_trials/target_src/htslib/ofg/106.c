#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "/src/htslib/htslib/sam.h" // Replacing bam.h with the correct path to sam.h

int LLVMFuzzerTestOneInput_106(const uint8_t *data, size_t size) {
    bam1_t bam_record;
    char tag[3];
    int64_t value;

    // Initialize bam_record with some non-NULL values
    memset(&bam_record, 0, sizeof(bam1_t));
    bam_record.data = (uint8_t *)data;
    bam_record.l_data = size;

    // Ensure the tag is a valid 2-character string
    if (size < 2) {
        return 0;
    }
    tag[0] = (char)data[0];
    tag[1] = (char)data[1];
    tag[2] = '\0';

    // Use the remaining data as the integer value
    if (size > 2) {
        value = *((int64_t *)(data + 2));
    } else {
        value = 0; // Default value if not enough data
    }

    // Call the function under test
    bam_aux_update_int(&bam_record, tag, value);

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

    LLVMFuzzerTestOneInput_106(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
