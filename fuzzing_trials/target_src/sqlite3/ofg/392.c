#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <string.h>  // Include for NULL
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_392(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *sql = "SELECT * FROM test WHERE id = ?1 AND name = ?2;";
    const char *param_name;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Use fuzzing data to determine which parameter index to use
    if (size < sizeof(int)) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    int index = *((int*)data) % 3; // Modulo by 3 to ensure index is within range of parameters

    // Call the function-under-test
    param_name = sqlite3_bind_parameter_name(stmt, index);

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}