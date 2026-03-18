#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_131(const uint8_t *data, size_t size) {
    // Initialize the sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);
    
    // Ensure the data is not empty
    if (size > 0 && str != NULL) {
        // Append the data to the sqlite3_str object
        sqlite3_str_append(str, (const char *)data, (int)size);
        
        // Call the function-under-test
        int length = sqlite3_str_length(str);
        
        // Use the length in some way to avoid compiler optimizations
        (void)length;
    }
    
    // Free the sqlite3_str object
    if (str != NULL) {
        sqlite3_str_finish(str);
    }
    
    return 0;
}