#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_732(const uint8_t *data, size_t size) {
    int64_t int_value = 0;

    if (size >= sizeof(int64_t)) {
        // Copy the first 8 bytes of data to int_value to ensure it's not zero
        int_value = *((int64_t*)data);
    } else {
        // If size is less than 8, use a default non-zero value
        int_value = 123456789;
    }

    // Instead of sqlite3_result_int64, use sqlite3_mprintf to test formatting
    char *formatted_string = sqlite3_mprintf("%lld", int_value);
    
    // Free the allocated memory to avoid memory leaks
    sqlite3_free(formatted_string);

    return 0;
}