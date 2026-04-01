#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_296(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt1 = NULL;
    sqlite3_stmt *stmt2 = NULL;
    int rc;
    
    // Open a new in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Create a dummy table to prepare statements
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, createTableSQL, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare two statements
    const char *sql1 = "INSERT INTO test (value) VALUES (?);";
    const char *sql2 = "INSERT INTO test (value) VALUES (?);";

    rc = sqlite3_prepare_v2(db, sql1, -1, &stmt1, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    rc = sqlite3_prepare_v2(db, sql2, -1, &stmt2, 0);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt1);
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the first statement
    rc = sqlite3_bind_text(stmt1, 1, (const char *)data, size, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt1);
        sqlite3_finalize(stmt2);
        sqlite3_close(db);
        return 0;
    }

    // Call the function-under-test
    sqlite3_transfer_bindings(stmt1, stmt2);

    // Finalize the statements and close the database
    sqlite3_finalize(stmt1);
    sqlite3_finalize(stmt2);
    sqlite3_close(db);

    return 0;
}