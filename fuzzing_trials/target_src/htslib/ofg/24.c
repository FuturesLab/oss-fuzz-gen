#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "/src/htslib/htslib/sam.h" // Include the correct header for bam1_t and bam_set_qname

int LLVMFuzzerTestOneInput_24(const uint8_t *data, size_t size) {
    // Ensure there is enough data to create a valid string
    if (size < 2) {
        return 0;
    }

    // Allocate memory for bam1_t structure
    bam1_t *bam_record = bam_init1();
    if (bam_record == NULL) {
        return 0;
    }

    // Create a null-terminated string from the data
    char *qname = (char *)malloc(size + 1);
    if (qname == NULL) {
        bam_destroy1(bam_record);
        return 0;
    }
    memcpy(qname, data, size);
    qname[size] = '\0'; // Null-terminate the string

    // Call the function under test
    int result = bam_set_qname(bam_record, qname);

    // Clean up
    free(qname);
    bam_destroy1(bam_record);

    return 0;
}