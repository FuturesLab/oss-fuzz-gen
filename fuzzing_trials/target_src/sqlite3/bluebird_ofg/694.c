#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_694(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql_create = "CREATE TABLE IF NOT EXISTS test (id INTEGER, value TEXT);";
    const char *sql_insert = "INSERT INTO test (id, value) VALUES (?, ?);";
    const char *text;
    int text_len;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Execute the CREATE TABLE statement
    rc = sqlite3_exec(db, sql_create, 0, 0, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Prepare the INSERT statement
    rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the integer value
    rc = sqlite3_bind_int(stmt, 1, 1);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Ensure the data is not NULL and has a size
    if (size > 0) {
        text_len = size < 100 ? size : 100; // Limit the text length to 100 characters
        text = (const char *)data;

        // Bind the text value
        rc = sqlite3_bind_text(stmt, 2, text, text_len, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 0;
        }
    } else {
        // If size is 0, bind an empty string
        rc = sqlite3_bind_text(stmt, 2, "", -1, SQLITE_TRANSIENT);
        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return 0;
        }
    }

    // Execute the statement
    rc = sqlite3_step(stmt);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database
    sqlite3_close(db);

    return 0;
}