#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *source_id = sqlite3_sourceid();

    // Print the source ID to ensure the function is called
    // (In a real fuzzing scenario, you might not print this, but it's here for demonstration)
    printf("SQLite3 Source ID: %s\n", source_id);

    return 0;
}