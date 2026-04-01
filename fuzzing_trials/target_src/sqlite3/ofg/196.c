#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_196(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated and non-empty
    if (size == 0) {
        return 0;
    }

    // Allocate memory for the database name and ensure it is null-terminated
    char *db_name = (char *)malloc(size + 1);
    if (db_name == NULL) {
        return 0;
    }
    memcpy(db_name, data, size);
    db_name[size] = '\0';

    sqlite3 *db = NULL;
    int result = sqlite3_open(db_name, &db);

    // Clean up
    if (db != NULL) {
        sqlite3_close(db);
    }
    free(db_name);

    return result;
}