#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "htslib/hts.h"
#include "htslib/sam.h"

int LLVMFuzzerTestOneInput_51(const uint8_t *data, size_t size) {
    htsFile *file = NULL;
    hts_itr_t *itr = NULL;
    void *data_out = malloc(1024); // Allocate memory for the output data

    if (size < 1) {
        free(data_out);
        return 0;
    }

    // Create a temporary file to store the input data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        free(data_out);
        return 0;
    }
    
    // Write the input data to the temporary file
    write(fd, data, size);
    close(fd);

    // Open the temporary file with htslib
    file = hts_open(tmpl, "r");
    if (file == NULL) {
        free(data_out);
        return 0;
    }

    // Initialize the iterator (this is just a placeholder, actual initialization may vary)
    itr = (hts_itr_t *)malloc(sizeof(hts_itr_t));
    if (itr == NULL) {
        hts_close(file);
        free(data_out);
        return 0;
    }

    // Call the function-under-test
    hts_itr_multi_next(file, itr, data_out);

    // Clean up
    free(itr);
    hts_close(file);
    free(data_out);
    unlink(tmpl); // Remove the temporary file

    return 0;
}