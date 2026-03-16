#include "stdint.h"
#include "stddef.h"
#include "string.h"
#include <stdlib.h>
#include "stdio.h"
#include "sqlite3.h"
#include "stdint.h"
#include "stdio.h"
#include <stdlib.h>
#include "string.h"

static void write_dummy_file(const uint8_t *Data, size_t Size) {
    FILE *file = fopen("./dummy_file", "wb");
    if (file) {
        fwrite(Data, 1, Size, file);
        fclose(file);
    }
}

int LLVMFuzzerTestOneInput_554(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    sqlite3 *db;
    sqlite3_stmt *stmt = NULL;
    char *errMsg = 0;
    int rc;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Create a dummy table
    const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare an INSERT statement
    sql = "INSERT INTO test (value) VALUES (?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind text data to the prepared statement
    sqlite3_bind_text(stmt, 1, (const char *)Data, Size, SQLITE_TRANSIENT);

    // Execute the statement
    rc = sqlite3_step(stmt);

    // Reset the statement
    sqlite3_reset(stmt);

    // Use sqlite3_sql to get the SQL string
    const char *sql_text = sqlite3_sql(stmt);

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Prepare a SELECT statement
    sql = "SELECT value FROM test;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Step through the results
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        // Get text from the first column
        const unsigned char *text = sqlite3_column_text(stmt, 0);

        // Use sqlite3_snprintf to format a string
        char buffer[100];
        sqlite3_snprintf(sizeof(buffer), buffer, "Value: %s", text);

        // Another snprintf with different format
        sqlite3_snprintf(sizeof(buffer), buffer, "Length: %d", (int)strlen((const char *)text));
    }

    // Reset the statement
    sqlite3_reset(stmt);

    // Finalize the statement
    if (stmt) {
        sqlite3_finalize(stmt);
    }

    // Close the database connection
    sqlite3_close(db);

    return 0;
}