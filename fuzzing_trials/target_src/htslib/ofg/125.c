#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "/src/htslib/htslib/sam.h" // Correct path for bam1_t and bam_set_qname

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    bam1_t bam_record;
    char qname[256]; // Assuming a maximum length for qname

    // Ensure that the size is enough to create a valid qname
    if (size < 1) {
        return 0;
    }

    // Initialize bam_record with some default values
    memset(&bam_record, 0, sizeof(bam1_t));

    // Copy data into qname ensuring null-termination
    size_t qname_length = size < sizeof(qname) ? size : sizeof(qname) - 1;
    memcpy(qname, data, qname_length);
    qname[qname_length] = '\0';

    // Call the function-under-test
    bam_set_qname(&bam_record, qname);

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

    LLVMFuzzerTestOneInput_125(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
