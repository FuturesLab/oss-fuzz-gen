#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "htslib/sam.h"

// Define a global variable to hold the input data and its size
static const uint8_t *global_data = NULL;
static size_t global_size = 0;
static size_t global_offset = 0;

// Define an iterator function that processes the input data
int iterator(void *data, bam1_t *b) {
    if (global_offset >= global_size) {
        return -1; // No more data to process
    }

    // Determine the size of data to copy for this iteration
    size_t copy_size = rand() % (global_size - global_offset + 1);
    if (copy_size == 0) {
        copy_size = 1; // Ensure at least one byte is processed
    }

    // Ensure bam1_t structure is properly initialized
    if (b->m_data < copy_size) {
        b->data = (uint8_t *)realloc(b->data, copy_size);
        b->m_data = copy_size;
    }
    memcpy(b->data, global_data + global_offset, copy_size);
    b->l_data = copy_size;

    // Advance the global offset
    global_offset += copy_size;

    return 0; // Successfully processed a read
}

int LLVMFuzzerTestOneInput_211(const uint8_t *data, size_t size) {
    bam_plp_t plp;
    int tid, n_plp;
    hts_pos_t pos;
    const bam_pileup1_t *pileup;

    // Set global data and size for the iterator function
    global_data = data;
    global_size = size;
    global_offset = 0;

    // Initialize bam_plp_t with the iterator function
    plp = bam_plp_init(iterator, NULL);

    if (plp == NULL) {
        return 0; // Failed to initialize, exit early
    }

    // Call the function-under-test
    while ((pileup = bam_plp64_auto(plp, &tid, &pos, &n_plp)) != NULL) {
        // Process the pileup data
        for (int i = 0; i < n_plp; ++i) {
            // Example processing: print the base
            printf("Base: %c\n", pileup[i].b->data[0]);
        }
    }

    // Clean up
    bam_plp_destroy(plp);

    return 0;
}