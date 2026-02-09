#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Function prototype for sqlite3_database_file_object
sqlite3_file *sqlite3_database_file_object(const char *filename);

int LLVMFuzzerTestOneInput_393(const uint8_t *data, size_t size) {
    // Ensure the input string is null-terminated and not too large
    char *input_str = NULL;
    sqlite3_file *file_object = NULL;

    // Allocate memory for the input string, ensuring it's not NULL
    if (size > 0 && size < 1024) {
        input_str = (char *)malloc(size + 1); // +1 for null terminator
        if (input_str == NULL) {
            return 0; // Memory allocation failed
        }
        memcpy(input_str, data, size);
        input_str[size] = '\0'; // Null-terminate the string
    } else {
        return 0; // Invalid size
    }

    // Call the function under test
    file_object = sqlite3_database_file_object(input_str);

    // Clean up
    free(input_str);

    // Return 0 to indicate successful execution
    return 0;
}