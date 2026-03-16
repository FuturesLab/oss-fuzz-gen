#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_763(const uint8_t *data, size_t size) {
    // Call the function-under-test
    const char *version = sqlite3_libversion();
    
    // Print the version to ensure the function is called
    printf("SQLite version: %s\n", version);

    return 0;
}