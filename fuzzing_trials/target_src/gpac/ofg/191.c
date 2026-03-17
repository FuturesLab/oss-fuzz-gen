#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <gpac/isomedia.h>  // Ensure this header is available for the function declaration

int LLVMFuzzerTestOneInput_191(const uint8_t *data, size_t size) {
    // Ensure we have enough data to extract an index
    if (size < sizeof(uint32_t)) {
        return 0;
    }

    // Extract an index from the input data
    uint32_t idx = *(const uint32_t *)data;

    // Validate the index to ensure it is within a reasonable range
    // Assuming the function expects a valid box type index, we should check against known valid indices
    // For example, if valid indices are between 0 and 1000, we should check this range
    if (idx > 1000) {  // Adjust this range based on actual valid indices
        return 0;
    }

    // Create a temporary file for the trace output
    char tmpl[] = "/tmp/fuzzfileXXXXXX";
    int fd = mkstemp(tmpl);
    if (fd == -1) {
        return 0;
    }

    // Open the file as a FILE* stream
    FILE *trace = fdopen(fd, "w+");
    if (!trace) {
        close(fd);
        return 0;
    }

    // Call the function under test
    gf_isom_dump_supported_box(idx, trace);

    // Clean up
    fclose(trace);
    remove(tmpl);

    return 0;
}