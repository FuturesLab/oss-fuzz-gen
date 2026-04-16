#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy

// Assuming sam_hdr_t is defined in a header file specific to the SAM library
#include <htslib/sam.h> // Include the necessary header for sam_hdr_t

int LLVMFuzzerTestOneInput_84(const uint8_t *data, size_t size) {
    sam_hdr_t *header = NULL;

    // Check if size is sufficient to create a dummy header
    if (size > 0) {
        // Allocate memory for sam_hdr_t (assuming a simple allocation for demonstration)
        header = (sam_hdr_t *)malloc(sizeof(sam_hdr_t));
        if (header == NULL) {
            return 0; // Return if memory allocation fails
        }

        // Initialize the header with some data
        // This is a placeholder; actual initialization would depend on the library
        header->n_targets = 1; // Example initialization
        header->target_name = (char **)malloc(sizeof(char *));
        if (header->target_name != NULL) {
            header->target_name[0] = (char *)malloc(size + 1);
            if (header->target_name[0] != NULL) {
                // Copy the data into the target name
                memcpy(header->target_name[0], data, size);
                header->target_name[0][size] = '\0'; // Null-terminate the string
            }
        }

        // Call the function-under-test
        sam_hdr_incr_ref(header);

        // Clean up
        if (header->target_name != NULL) {
            free(header->target_name[0]);
            free(header->target_name);
        }
        free(header);
    }

    return 0;
}