#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_266(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    char *errMsg = NULL;
    char **result = NULL;
    int rows = 0;
    int columns = 0;

    // Initialize SQLite in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Ensure the input data is null-terminated and treat it as an SQL query
    char *query = (char *)malloc(size + 1);
    if (query == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(query, data, size);
    query[size] = '\0';

    // Call the function-under-test
    sqlite3_get_table(db, query, &result, &rows, &columns, &errMsg);

    // Clean up
    if (result != NULL) {
        sqlite3_free_table(result);
    }
    if (errMsg != NULL) {
        sqlite3_free(errMsg);
    }
    free(query);
    sqlite3_close(db);

    return 0;
}