#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

// Dummy destructor_4 function to satisfy the function signature
void dummy_destructor_4(void *ptr) {
    // No operation performed
}

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_4(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (data BLOB);";

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data as a blob to the SQL statement
    rc = sqlite3_bind_blob64(stmt, 1, (const void *)data, (sqlite3_uint64)size, dummy_destructor_4);

    // Finalize the statement and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

#ifdef __cplusplus
}
#endif