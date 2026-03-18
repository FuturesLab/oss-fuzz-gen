#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>  // Include this for malloc and free

int LLVMFuzzerTestOneInput_45(const uint8_t *data, size_t size) {
    // Initialize a sqlite3_str object
    sqlite3_str *str = sqlite3_str_new(NULL);
    
    // Ensure the data is not empty
    if (size > 0) {
        // Use the data as a string input
        const char *input = (const char *)data;
        
        // Ensure the string is null-terminated
        char *null_terminated_input = (char *)malloc(size + 1);
        memcpy(null_terminated_input, input, size);
        null_terminated_input[size] = '\0';
        
        // Call the function-under-test
        sqlite3_str_append(str, null_terminated_input, (int)size);
        
        // Free the allocated memory
        free(null_terminated_input);
    }
    
    // Free the sqlite3_str object
    sqlite3_str_finish(str);
    
    return 0;
}