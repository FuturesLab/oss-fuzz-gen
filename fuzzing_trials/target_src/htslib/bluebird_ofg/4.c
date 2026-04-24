#include <sys/stat.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "htslib/hts.h"
#include "/src/htslib/htslib/thread_pool.h"
#include "htslib/sam.h" // Include for SAM/BAM/CRAM file operations

// Function to create a temporary file from the fuzzing input
static htsFile* create_temp_file_from_input(const uint8_t *data, size_t size) {
    char filename[] = "/tmp/fuzz_input_XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return NULL;
    }

    // Write the input data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(filename);
        return NULL;
    }
    close(fd);

    // Open the file with htslib
    htsFile *file = hts_open(filename, "r");
    unlink(filename); // Remove the file after opening
    return file;
}

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    // Check if the input size is reasonable for a SAM/BAM/CRAM file
    if (size < 4) {
        return 0; // Return early if the input size is too small
    }

    // Create a temporary file from the input data
    htsFile *file = create_temp_file_from_input(data, size);
    if (file == NULL) {
        return 0; // If file opening fails, return early
    }
    
    htsThreadPool thread_pool;
    struct hts_tpool *tpool = hts_tpool_init(2); // Initialize a thread pool with 2 threads
    if (tpool == NULL) {
        hts_close(file);
        return 0; // If thread pool initialization fails, return early
    }
    thread_pool.pool = tpool;
    thread_pool.qsize = 0; // Default queue size

    // Call the function-under-test
    int result = hts_set_thread_pool(file, &thread_pool);
    if (result != 0) {
        hts_tpool_destroy(tpool);
        hts_close(file);
        return 0; // If setting the thread pool fails, return early
    }

    // Read the header to ensure the file is valid
    bam_hdr_t *header = sam_hdr_read(file);
    if (header == NULL) {
        hts_tpool_destroy(tpool);
        hts_close(file);
        return 0; // If reading the header fails, return early
    }

    // Perform operations that require the thread pool
    bam1_t *aln = bam_init1();
    if (aln == NULL) {
        bam_hdr_destroy(header);
        hts_tpool_destroy(tpool);
        hts_close(file);
        return 0; // If bam initialization fails, return early
    }

    while (sam_read1(file, header, aln) >= 0) {
        // Process each alignment
    }

    // Begin mutation: Producer.SPLICE_MUTATOR - Spliced data flow from bam_init1 to bam_aux_update_float using the plateau pool
    char tag[3] = {0};
    float value;
    // Ensure dataflow is valid (i.e., non-null)
    if (!aln) {
    	return 0;
    }
    int ret_bam_aux_update_float_maaqx = bam_aux_update_float(aln, tag, value);
    if (ret_bam_aux_update_float_maaqx < 0){
    	return 0;
    }
    // End mutation: Producer.SPLICE_MUTATOR
    
    bam_destroy1(aln);
    bam_hdr_destroy(header);

    // Ensure all operations are completed before destroying the thread pool

    // Clean up
    hts_close(file);
    hts_tpool_destroy(tpool);

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

    LLVMFuzzerTestOneInput_4(data + 1, (size_t)(size - 1));

    free(data);
    fclose(f);
    return 0;
}
#endif
