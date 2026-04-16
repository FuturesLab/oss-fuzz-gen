#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <htslib/hts.h>
#include <htslib/sam.h>

int LLVMFuzzerTestOneInput_132(const uint8_t *data, size_t size) {
    // Ensure size is sufficient to create a valid string and some BAM content
    if (size < 5) { // Adjusted to ensure there's enough data for a filter expression
        return 0;
    }

    // Create a temporary file to simulate an htsFile
    const char *temp_filename = "/tmp/temp_hts_file.bam";
    FILE *temp_file = fopen(temp_filename, "wb");
    if (temp_file == NULL) {
        return 0;
    }

    // Write some valid BAM header to the temporary file to ensure it can be opened by hts_open
    const char *bam_header = "BAM\x01"; // A minimal BAM header
    fwrite(bam_header, 1, 4, temp_file);

    // Write some dummy BAM content to the file
    const char *bam_content = "\x00\x00\x00\x00"; // Minimal content; adjust as needed
    fwrite(bam_content, 1, 4, temp_file);
    fclose(temp_file);

    // Open the temporary file as an htsFile
    htsFile *hts_file = hts_open(temp_filename, "r");
    if (hts_file == NULL) {
        return 0;
    }

    // Copy the data to create a null-terminated string for the filter expression
    char *filter_expression = (char *)malloc(size + 1);
    if (filter_expression == NULL) {
        hts_close(hts_file);
        return 0;
    }
    memcpy(filter_expression, data, size);
    filter_expression[size] = '\0';

    // Ensure the filter expression is not empty
    if (filter_expression[0] == '\0') {
        free(filter_expression);
        hts_close(hts_file);
        remove(temp_filename);
        return 0;
    }

    // Call the function-under-test
    int result = hts_set_filter_expression(hts_file, filter_expression);

    // Check the result of setting the filter expression
    if (result != 0) {
        // Handle error if needed
    }

    // Clean up
    free(filter_expression);
    hts_close(hts_file);
    remove(temp_filename);

    return 0;
}