#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

// A simple SQLite database setup for fuzzing
static sqlite3 *db = NULL;
static sqlite3_stmt *stmt = NULL;

__attribute__((constructor))
void setup() {
    // Initialize the SQLite database in memory
    sqlite3_open(":memory:", &db);

    // Create a table for testing
    sqlite3_exec(db, "CREATE TABLE test (id INTEGER, value TEXT);", 0, 0, 0);

    // Insert some data into the table
    sqlite3_exec(db, "INSERT INTO test (id, value) VALUES (1, 'hello');", 0, 0, 0);
    sqlite3_exec(db, "INSERT INTO test (id, value) VALUES (2, 'world');", 0, 0, 0);

    // Prepare a statement to select data from the table
    sqlite3_prepare_v2(db, "SELECT value FROM test WHERE id = ?;", -1, &stmt, 0);
}

__attribute__((destructor))
void cleanup() {
    // Clean up the SQLite resources
    if (stmt) {
        sqlite3_finalize(stmt);
    }
    if (db) {
        sqlite3_close(db);
    }
}

int LLVMFuzzerTestOneInput_188(const uint8_t *data, size_t size) {
    // Ensure we have at least 4 bytes to read an integer for the parameter
    if (size < sizeof(int)) {
        return 0;
    }

    // Extract an integer from the input data to use as the parameter
    int id = *((int *)data);

    // Bind the integer to the prepared statement
    if (sqlite3_bind_int(stmt, 1, id) != SQLITE_OK) {
        return 0;
    }

    // Execute the statement
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call the function-under-test
        int bytes = sqlite3_column_bytes(stmt, 0);

        // Use the result to prevent optimization out
        volatile int prevent_opt = bytes;
        (void)prevent_opt;
    }

    // Reset the statement for the next run
    sqlite3_reset(stmt);

    return 0;
}