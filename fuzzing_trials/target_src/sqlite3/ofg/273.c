#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

// Callback function for sqlite3_exec
int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int LLVMFuzzerTestOneInput_273(const uint8_t *data, size_t size) {
    sqlite3 *db;
    char *errMsg = NULL;
    int rc;
    
    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure the data is null-terminated for use as a SQL statement
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(sql, data, size);
    sql[size] = '\0';

    // Execute the SQL statement
    sqlite3_exec(db, sql, callback, NULL, &errMsg);

    // Free resources
    free(sql);
    if (errMsg != NULL) {
        sqlite3_free(errMsg);
    }
    sqlite3_close(db);

    return 0;
}