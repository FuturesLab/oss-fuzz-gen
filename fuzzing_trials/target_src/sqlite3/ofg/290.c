#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_290(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    // Ensure that the data is not NULL and has a valid size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare a statement
    rc = sqlite3_prepare_v2(db, "SELECT ?;", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data as a blob
    rc = sqlite3_bind_blob(stmt, 1, data, size, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    rc = sqlite3_step(stmt);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database
    sqlite3_close(db);

    return 0;
}