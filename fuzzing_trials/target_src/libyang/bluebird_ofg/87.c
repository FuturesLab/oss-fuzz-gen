#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include "/src/libyang/src/tree_data.h" // Corrected include path for ly_time_str2ts

int LLVMFuzzerTestOneInput_87(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated for string processing
    if (size == 0) {
        return 0; // Exit early if there's no data to process
    }

    char *input_str = (char *)malloc(size + 1);
    if (!input_str) {
        return 0; // Exit if memory allocation fails
    }
    memcpy(input_str, data, size);
    input_str[size] = '\0';

    struct timespec ts;

    // Basic validation to ensure the input is a valid time string
    // For example, check if the input string contains valid characters for a time string
    // This is a simple heuristic and can be adjusted based on the expected format
    if (strspn(input_str, "0123456789-:T ") != size) {
        free(input_str);
        return 0; // Exit if the input is not a valid time string
    }

    // Call the function-under-test and check for errors
    int result = ly_time_str2ts(input_str, &ts);
    if (result != 0) {
        // Handle the error, e.g., log it or ignore it for fuzzing
        fprintf(stderr, "Error parsing time string: %s, errno: %d\n", input_str, errno);
    } else {
        // Optionally, you can print or log the successful conversion
        printf("Successfully parsed time string: %s\n", input_str);
    }

    // Free the allocated memory
    free(input_str);

    return 0;
}