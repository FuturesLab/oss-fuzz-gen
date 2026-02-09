#include <stdio.h>
#include <sqlite3.h>
#include <stdint.h> // Include this for uint8_t
#include <stddef.h> // Include this for size_t

int LLVMFuzzerTestOneInput_236(const uint8_t *data, size_t size) {
    // The function sqlite3_libversion() does not take any parameters,
    // so we will simply call it directly.

    // Call the function under test
    const char *version = sqlite3_libversion();

    // For demonstration purposes, we can print the version.
    // In a fuzzing context, we typically wouldn't print, but this is
    // just to show that we've called the function.
    if (version != NULL) {
        printf("SQLite version: %s\n", version);
    } else {
        printf("Failed to get SQLite version.\n");
    }

    return 0;
}