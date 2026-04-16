#include <stdint.h>
#include <stdlib.h>
#include <htslib/hts.h>
#include <stdio.h>

int LLVMFuzzerTestOneInput_196(const uint8_t *data, size_t size) {
    // Ensure there is enough data to extract an integer
    if (size < sizeof(int)) {
        return 0;
    }
    
    // Create a temporary file for writing
    FILE *temp_file = tmpfile();
    if (!temp_file) {
        return 0;
    }

    // Initialize htsFile pointer using the temporary file
    htsFile *file = hts_hopen(temp_file, "temp.bam", "wb");
    if (!file) {
        fclose(temp_file);
        return 0;
    }

    // Extract an integer from the input data
    int threads = *(int *)data;

    // Ensure threads is a positive number
    if (threads < 1) {
        threads = 1;
    }

    // Call the function-under-test
    int result = hts_set_threads(file, threads);

    // Clean up
    hts_close(file);
    fclose(temp_file);

    return 0;
}