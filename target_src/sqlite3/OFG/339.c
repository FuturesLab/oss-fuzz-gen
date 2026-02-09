#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_339(const uint8_t *data, size_t size) {
    // Ensure the input data is not NULL and has a reasonable size
    if (size < 2) { // Ensure there is enough data for two strings
        return 0;
    }

    // Allocate memory for the two strings to be used in sqlite3_strglob
    // We will use the first half of the input data for the first string
    // and the second half for the second string.
    size_t half_size = size / 2;

    // Allocate memory for the first pattern string
    char *pattern = (char *)malloc(half_size + 1);
    if (pattern == NULL) {
        return 0; // Memory allocation failed
    }
    memcpy(pattern, data, half_size);
    pattern[half_size] = '\0'; // Null-terminate the string

    // Allocate memory for the second string to match against
    // Ensure that we allocate at least one byte for string_to_match
    size_t match_size = size - half_size;
    if (match_size < 1) {
        free(pattern);
        return 0; // Not enough data for the second string
    }
    
    char *string_to_match = (char *)malloc(match_size + 1);
    if (string_to_match == NULL) {
        free(pattern);
        return 0; // Memory allocation failed
    }
    memcpy(string_to_match, data + half_size, match_size);
    string_to_match[match_size] = '\0'; // Null-terminate the string

    // Call the function under test only if both strings are non-empty
    // Ensure the pattern is not empty and contains valid glob characters
    if (strlen(pattern) > 0 && strlen(string_to_match) > 0) {
        // Call the function under test
        int result = sqlite3_strglob(pattern, string_to_match);

        // Clean up allocated memory
        free(pattern);
        free(string_to_match);
        return result;
    }

    // Clean up allocated memory if the strings are not valid
    free(pattern);
    free(string_to_match);
    return 0;
}

#ifdef __cplusplus
}
#endif