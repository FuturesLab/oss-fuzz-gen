#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_33(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    if (size == 0) {
        return 0;
    }

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a statement using the input data
    rc = sqlite3_prepare_v2(db, (const char *)data, size, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    int isExplain = sqlite3_stmt_isexplain(stmt);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}