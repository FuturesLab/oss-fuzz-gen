#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// Function signature for the function-under-test
int sam_index_build(const char *filename, int option);

int LLVMFuzzerTestOneInput_60(const uint8_t *data, size_t size) {
    // Ensure the fuzz data is not empty
    if (size == 0) {
        return 0;
    }

    // Create a temporary file to store the fuzz data
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        perror("mkstemp failed");
        return 0;
    }

    // Write the fuzz data to the temporary file
    if (write(fd, data, size) != (ssize_t)size) {
        perror("write failed");
        close(fd);
        unlink(tmpl);
        return 0;
    }

    // Ensure the file is closed before being used by the function-under-test
    close(fd);

    // Set appropriate permissions for the temporary file
    chmod(tmpl, S_IRUSR | S_IWUSR);

    // Call the function-under-test with the temporary file and a non-zero option

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sam_index_build

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of sam_index_build
    int result = sam_index_build(tmpl, -1);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (result != 0) {
        fprintf(stderr, "sam_index_build failed with error code: %d\n", result);
    }

    // Clean up the temporary file

    // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sam_index_build to bam_auxB2f

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function hts_close with hts_flush
    int ret_hts_close_jvvvq = hts_flush(NULL);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR


    if (ret_hts_close_jvvvq < 0){
    	return 0;
    }


    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of bam_auxB2f
    const uint8_t evdlygxb = -1;
    double ret_bam_auxB2f_fcngy = bam_auxB2f(&evdlygxb, (uint32_t)ret_hts_close_jvvvq);
    // End mutation: Producer.REPLACE_ARG_MUTATOR


    if (ret_bam_auxB2f_fcngy < 0){
    	return 0;
    }

    // End mutation: Producer.APPEND_MUTATOR

    unlink(tmpl);

    return 0;
}