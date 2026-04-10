#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>      // For close, unlink, write
#include <fcntl.h>       // For mkstemp
#include "htslib/hts.h"
#include "/src/htslib/htslib/thread_pool.h"  // For hts_tpool and related functions
#include "htslib/sam.h"  // For sam_read1 and bam1_t

int LLVMFuzzerTestOneInput_227(const uint8_t *data, size_t size) {
    // Check if the size is reasonable for hts_open to process
    if (size < 4) {
        return 0; // Not enough data to process
    }

    // Create a temporary file to simulate input data
    char filename[] = "/tmp/fuzz_input.XXXXXX";
    int fd = mkstemp(filename);
    if (fd == -1) {
        return 0;
    }

    // Write the fuzzing data to the temporary file
    if (write(fd, data, size) != size) {
        close(fd);
        unlink(filename);
        return 0;
    }
    close(fd);

    // Open the temporary file with hts_open
    htsFile *file = hts_open(filename, "r");
    if (file == NULL) {
        unlink(filename);
        return 0;
    }

    htsThreadPool threadPool;
    struct hts_tpool *pool = hts_tpool_init(1); // Initialize a thread pool with 1 thread
    if (pool == NULL) {
        hts_close(file);
        unlink(filename);
        return 0;
    }

    threadPool.pool = pool;
    threadPool.qsize = 0; // Set the queue size to 0 for simplicity

    // Set the thread pool for the file
    int result = hts_set_thread_pool(file, &threadPool);
    if (result != 0) {
        hts_tpool_destroy(pool);
        hts_close(file);
        unlink(filename);
        return 0;
    }

    // Simulate processing by reading from the file
    bam_hdr_t *header = sam_hdr_read(file);
    if (header != NULL) {
        bam1_t *aln = bam_init1();
        while (sam_read1(file, header, aln) >= 0) {
            // Process the alignment (placeholder for actual logic)
        }
        bam_destroy1(aln);
        bam_hdr_destroy(header);
    }

    // Clean up in the correct order

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with hts_check_EOF
    hts_check_EOF(file);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    hts_tpool_destroy(pool);
    unlink(filename);

    return 0;
}