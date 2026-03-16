// This fuzz driver is generated for library sqlite3, aiming to fuzz the following functions:
// sqlite3_prepare_v2 at sqlite3.c:132572:16 in sqlite3.h
// sqlite3_bind_text at sqlite3.c:80158:16 in sqlite3.h
// sqlite3_open at sqlite3.c:174695:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_reset at sqlite3.c:78461:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_step at sqlite3.c:79246:16 in sqlite3.h
// sqlite3_errmsg at sqlite3.c:173721:24 in sqlite3.h
// sqlite3_reset at sqlite3.c:78461:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
// sqlite3_changes at sqlite3.c:172160:16 in sqlite3.h
// sqlite3_finalize at sqlite3.c:78432:16 in sqlite3.h
// sqlite3_close at sqlite3.c:172361:16 in sqlite3.h
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

static int execute_sql(sqlite3 *db, const char *sql, sqlite3_stmt **stmt) {
    int rc = sqlite3_prepare_v2(db, sql, -1, stmt, NULL);
    if (rc != SQLITE_OK) {
        return rc;
    }
    return SQLITE_OK;
}

static int bind_text_to_stmt(sqlite3_stmt *stmt, const char *text) {
    return sqlite3_bind_text(stmt, 1, text, -1, SQLITE_TRANSIENT);
}

int LLVMFuzzerTestOneInput_27(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, value TEXT);"
                      "INSERT INTO test (value) VALUES (?);";

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare the SQL statement
    rc = execute_sql(db, sql, &stmt);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Reset the statement
    rc = sqlite3_reset(stmt);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Bind data as text
    rc = bind_text_to_stmt(stmt, (const char *)Data);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Step through the statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        // Get error message if step fails
        const char *errmsg = sqlite3_errmsg(db);
        (void)errmsg; // Suppress unused variable warning
    }

    // Reset the statement again
    rc = sqlite3_reset(stmt);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Check the number of changes
    int changes = sqlite3_changes(db);
    (void)changes; // Suppress unused variable warning

    // Finalize and close the database
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}