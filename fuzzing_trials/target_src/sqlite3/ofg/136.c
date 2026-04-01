#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_136(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    int index = 0;
    void *pointer = (void *)0x1; // Non-NULL arbitrary pointer
    const char *type = "example_type";
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY);";

    // Open an in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Prepare a simple SQL statement
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    sqlite3_bind_pointer(stmt, index, pointer, type, NULL);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}