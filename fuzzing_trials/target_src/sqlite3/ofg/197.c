#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_197(const uint8_t *data, size_t size) {
    // Ensure that the input size is within a reasonable limit for SQLite options
    if (size == 0 || size > 255) {
        return 0; // Skip if the size is out of bounds
    }

    // Allocate memory for the option string
    char option[256]; // 255 characters + 1 for null terminator
    // Copy the input data to the option string, ensuring null termination
    for (size_t i = 0; i < size; i++) {
        option[i] = (char)data[i];
    }
    option[size] = '\0'; // Null terminate the string

    // Call the function under test
    int result = sqlite3_compileoption_used(option);

    // Optionally, you can handle the result here if needed
    return result;
}