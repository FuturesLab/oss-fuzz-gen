#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_293(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt1 = NULL;
    sqlite3_stmt *stmt2 = NULL;
    int rc;

    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare two simple SQL statements
    const char *sql1 = "SELECT ?1, ?2";
    const char *sql2 = "SELECT ?3, ?4";

    rc = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    rc = sqlite3_prepare_v2(db, sql2, -1, &stmt2, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(stmt1);
        sqlite3_close(db);
        return 0;
    }

    // Use the input data to bind values to the first statement
    if (size > 0) {
        sqlite3_bind_int(stmt1, 1, data[0]);
    }
    if (size > 1) {
        sqlite3_bind_text(stmt1, 2, (const char*)&data[1], size - 1, SQLITE_TRANSIENT);
    }

    // Transfer bindings from stmt1 to stmt2
    sqlite3_transfer_bindings(stmt1, stmt2);

    // Execute the statements to increase code coverage
    sqlite3_step(stmt1);
    sqlite3_step(stmt2);

    // Clean up
    sqlite3_finalize(stmt1);
    sqlite3_finalize(stmt2);
    sqlite3_close(db);

    return 0;
}