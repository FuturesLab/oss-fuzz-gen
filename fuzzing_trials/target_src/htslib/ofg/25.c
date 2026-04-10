#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <htslib/sam.h> // Ensure you have the htslib library installed
#include <stdlib.h>     // Include the standard library for malloc and free

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Declare and initialize the bam1_t structure
    bam1_t *bam_record = bam_init1();
    if (bam_record == NULL) {
        return 0; // Exit if memory allocation fails
    }

    // Ensure the data size is sufficient for a null-terminated string
    if (size == 0 || data[size - 1] != '\0') {
        // Create a buffer with null termination
        char *qname = (char *)malloc(size + 1);
        if (qname == NULL) {
            bam_destroy1(bam_record);
            return 0; // Exit if memory allocation fails
        }
        memcpy(qname, data, size);
        qname[size] = '\0'; // Null-terminate the string

        // Call the function-under-test
        bam_set_qname(bam_record, qname);

        // Free the allocated memory
        free(qname);
    } else {
        // If data is already null-terminated, directly use it
        bam_set_qname(bam_record, (const char *)data);
    }

    // Clean up
    bam_destroy1(bam_record);

    return 0;
}