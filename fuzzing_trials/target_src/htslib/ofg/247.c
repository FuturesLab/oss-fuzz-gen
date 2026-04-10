#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

// Assuming sam_hdr_t is defined in an included header file
typedef struct {
    // Dummy structure for demonstration purposes
    int dummy;
} sam_hdr_t;

// Dummy function to represent the function-under-test
int sam_hdr_update_line_247(sam_hdr_t *hdr, const char *arg1, const char *arg2, const char *arg3, void *arg4) {
    // Implementation is not provided here
    return 0;
}

int LLVMFuzzerTestOneInput_247(const uint8_t *data, size_t size) {
    // Ensure there's enough data for the minimum required input
    if (size < 4) {
        return 0;
    }

    // Initialize the sam_hdr_t structure
    sam_hdr_t hdr;
    hdr.dummy = 0; // Initialize with a default value

    // Split the input data into parts for the string arguments
    size_t part_size = size / 4;
    size_t remaining_size = size - 3 * part_size;

    char *arg1 = (char *)malloc(part_size + 1);
    char *arg2 = (char *)malloc(part_size + 1);
    char *arg3 = (char *)malloc(part_size + 1);

    if (!arg1 || !arg2 || !arg3) {
        free(arg1);
        free(arg2);
        free(arg3);
        return 0;
    }

    // Copy data into the strings and null-terminate them
    memcpy(arg1, data, part_size);
    arg1[part_size] = '\0';
    memcpy(arg2, data + part_size, part_size);
    arg2[part_size] = '\0';
    memcpy(arg3, data + 2 * part_size, part_size);
    arg3[part_size] = '\0';

    // Use the remaining data as a void pointer
    void *arg4 = NULL;
    if (remaining_size > 0) {
        arg4 = (void *)(data + 3 * part_size);
    }

    // Call the function-under-test
    sam_hdr_update_line_247(&hdr, arg1, arg2, arg3, arg4);

    // Free allocated memory
    free(arg1);
    free(arg2);
    free(arg3);

    return 0;
}