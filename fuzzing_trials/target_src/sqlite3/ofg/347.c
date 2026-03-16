#include <stdint.h>
#include <sqlite3.h>
#include <stdio.h>
#include <string.h>

// A simple callback function for collation needed
int collation_needed_callback_347(void *pArg, sqlite3 *db, int eTextRep, const char *zCollName) {
    printf("Collation needed: %s\n", zCollName);
    return 0;
}

int LLVMFuzzerTestOneInput_347(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    void *pArg = (void *)1; // Non-NULL pointer
    char *errMsg = NULL;

    // Open an in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Call the function-under-test with a valid callback
    sqlite3_collation_needed(db, pArg, collation_needed_callback_347);

    // Create a table and insert data
    const char *createTableSQL = "CREATE TABLE test (id INTEGER PRIMARY KEY, name TEXT);";
    if (sqlite3_exec(db, createTableSQL, 0, 0, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Insert data into the table
    const char *insertSQL = "INSERT INTO test (name) VALUES ('Alice'), ('Bob'), ('Charlie');";
    if (sqlite3_exec(db, insertSQL, 0, 0, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Execute a query that requires collation
    const char *querySQL = "SELECT name FROM test ORDER BY name COLLATE NOCASE;";
    if (sqlite3_exec(db, querySQL, 0, 0, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}