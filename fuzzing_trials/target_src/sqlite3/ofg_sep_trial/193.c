#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_193(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated and not empty
    if (size == 0) return 0;
    
    char *filename = (char *)malloc(size + 1);
    if (filename == NULL) return 0;
    
    memcpy(filename, data, size);
    filename[size] = '\0'; // Null-terminate the string

    sqlite3 *db = NULL;
    int result = sqlite3_open(filename, &db);

    // Clean up
    if (db != NULL) {
        sqlite3_close(db);
    }
    free(filename);

    return 0;
}