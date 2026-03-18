#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

// Dummy function to act as a callback for the user-defined functions
static void dummy_function_384(sqlite3_context *context, int argc, sqlite3_value **argv) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_384(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    const char *func_name = "test_function";
    int nArg = 1;
    int eTextRep = SQLITE_UTF8;
    void *pApp = NULL;
    sqlite3_stmt *stmt = NULL;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure data is not NULL and has a reasonable size
    if (data == NULL || size == 0) {
        sqlite3_close(db);
        return 0;
    }

    // Create a user-defined function in SQLite
    rc = sqlite3_create_function(
        db,
        func_name,
        nArg,
        eTextRep,
        pApp,
        dummy_function_384,
        NULL,
        NULL
    );

    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare an SQL statement that uses the user-defined function
    const char *sql = "SELECT test_function(?)";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the SQL statement
    rc = sqlite3_bind_blob(stmt, 1, data, size, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}