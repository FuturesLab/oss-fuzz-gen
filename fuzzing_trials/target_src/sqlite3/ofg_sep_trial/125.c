#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_125(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    int rc;
    
    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }
    
    // Ensure the data is null-terminated for SQLite statement preparation
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';
    
    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc == SQLITE_OK && stmt != NULL) {
        // Call the function-under-test
        int readonly = sqlite3_stmt_readonly(stmt);
        
        // Use the result in some way (e.g., print, log, etc.)
        // Here, we will just suppress unused variable warning
        (void)readonly;
        
        // Finalize the statement
        sqlite3_finalize(stmt);
    }
    
    // Clean up
    free(sql);
    sqlite3_close(db);
    
    return 0;
}