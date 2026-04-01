#include <stddef.h>
#include <stdint.h>
#include <sqlite3.h>

// Fuzzing harness for the function sqlite3_changes
#ifdef __cplusplus
extern "C" {
#endif
    int LLVMFuzzerTestOneInput_263(const uint8_t *data, size_t size) {
        sqlite3 *db = NULL;
        int rc;
        
        // Open an in-memory SQLite database
        rc = sqlite3_open(":memory:", &db);
        if (rc != SQLITE_OK) {
            return 0;
        }
        
        // Execute a simple SQL statement to ensure the database is in a valid state
        const char *sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
        sqlite3_exec(db, sql, 0, 0, 0);
        
        // Call the function-under-test
        int changes = sqlite3_changes(db);
        
        // Close the database connection
        sqlite3_close(db);
        
        return 0;
    }
#ifdef __cplusplus
}
#endif