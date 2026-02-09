#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_122(const uint8_t *data, size_t size) {
    sqlite3 *db;
    const char *txn_name;
    int result;

    // Initialize the SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Ensure the size is non-zero and create a string for the transaction name
    if (size > 0) {
        // Create a null-terminated string for the transaction name
        txn_name = (const char *)malloc(size + 1);
        if (txn_name == NULL) {
            sqlite3_close(db);
            return 0; // Memory allocation failed
        }
        memcpy((void *)txn_name, data, size);
        ((char *)txn_name)[size] = '\0'; // Null-terminate the string
    } else {
        txn_name = "default_txn"; // Fallback transaction name
    }

    // Start a transaction
    char *errMsg = 0;
    char sql[256];
    snprintf(sql, sizeof(sql), "BEGIN TRANSACTION %s;", txn_name);
    
    // Execute the SQL command to begin a transaction
    result = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (result != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    // Clean up
    if (size > 0) {
        free((void *)txn_name);
    }
    sqlite3_close(db);

    return result;
}

#ifdef __cplusplus
}
#endif