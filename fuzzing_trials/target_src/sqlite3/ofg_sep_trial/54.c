#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_54(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;  // NULL is defined in stddef.h
    int rc;
    char *errMsg = 0;

    // Open a new database connection in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a simple table
    const char *sql = "CREATE TABLE test(id INT, value TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Insert data into the table using the fuzzer input
    sqlite3_stmt *stmt;
    const char *insert_sql = "INSERT INTO test(id, value) VALUES(?, ?);";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        // Bind the fuzzer input data
        if (size > 0) {
            sqlite3_bind_int(stmt, 1, data[0]);
        }
        if (size > 1) {
            sqlite3_bind_text(stmt, 2, (const char *)data + 1, size - 1, SQLITE_TRANSIENT);
        }

        // Execute the statement
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
    }

    // Call the function-under-test
    sqlite3_int64 changes = sqlite3_changes64(db);

    // Clean up
    sqlite3_close(db);

    return 0;
}