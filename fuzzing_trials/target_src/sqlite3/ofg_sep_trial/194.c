#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_194(const uint8_t *data, size_t size) {
    // Ensure the data is null-terminated to be used as a string
    char *db_name = (char *)malloc(size + 1);
    if (db_name == NULL) {
        return 0; // Handle allocation failure
    }
    memcpy(db_name, data, size);
    db_name[size] = '\0'; // Null-terminate the string

    sqlite3 *db = NULL;

    // Call the function-under-test
    int result = sqlite3_open(db_name, &db);

    // Clean up
    if (db != NULL) {
        sqlite3_close(db);
    }
    free(db_name);

    return 0;
}