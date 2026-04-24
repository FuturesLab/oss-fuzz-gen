#include <stdint.h>
#include <stdlib.h>
#include <htslib/sam.h>
#include <string.h>

int LLVMFuzzerTestOneInput_160(const uint8_t *data, size_t size) {
    if (size < sizeof(bam1_t)) {
        return 0; // Not enough data to create a bam1_t structure
    }

    // Allocate memory for bam1_t
    bam1_t *bam_record = (bam1_t *)malloc(sizeof(bam1_t));
    if (bam_record == NULL) {
        return 0; // Memory allocation failed
    }

    // Allocate memory for the data field in bam1_t
    bam_record->data = (uint8_t *)malloc(size);
    if (bam_record->data == NULL) {
        free(bam_record);
        return 0; // Memory allocation failed
    }

    // Copy the input data into bam_record->data
    memcpy(bam_record->data, data, size);
    bam_record->m_data = size;
    bam_record->l_data = size;

    // Call the function-under-test
    hts_pos_t end_position = bam_endpos(bam_record);

    // Clean up
    free(bam_record->data);
    free(bam_record);

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

    LLVMFuzzerTestOneInput_160(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
