#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_168(const uint8_t *data, size_t size) {
    // Initialize necessary variables
    sqlite3_str *str;
    int num_chars;
    char append_char;

    // Ensure size is sufficient to extract required data
    if (size < sizeof(int) + sizeof(char)) {
        return 0;
    }

    // Create a new sqlite3_str object
    str = sqlite3_str_new(NULL);

    // Extract num_chars and append_char from the input data
    num_chars = (int)data[0];  // Use the first byte as the number of characters
    append_char = (char)data[1];  // Use the second byte as the character to append

    // Call the function-under-test
    sqlite3_str_appendchar(str, num_chars, append_char);

    // Clean up
    sqlite3_str_finish(str);

    return 0;
}