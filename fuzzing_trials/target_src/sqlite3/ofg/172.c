#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <stddef.h> // Include for size_t

int LLVMFuzzerTestOneInput_172(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    const char *db_name = "test.db"; // A valid database name
    int *pNumWalFrames = (int *)malloc(sizeof(int));
    int *pNumCheckpointed = (int *)malloc(sizeof(int));
    
    // Initialize SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        free(pNumWalFrames);
        free(pNumCheckpointed);
        return 0; // Failed to open database
    }

    // Prepare a dummy database to ensure it's not NULL
    if (size > 0) {
        char *sql = (char *)malloc(size + 1);
        memcpy(sql, data, size);
        sql[size] = '\0'; // Null-terminate the string

        // Create a table for testing
        char *errMsg;
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            sqlite3_free(errMsg);
            free(sql);
            sqlite3_close(db);
            free(pNumWalFrames);
            free(pNumCheckpointed);
            return 0; // Failed to execute SQL
        }
        free(sql);
    }

    // Initialize the checkpoint parameters
    *pNumWalFrames = 0;
    *pNumCheckpointed = 0;

    // Call the function under test
    rc = sqlite3_wal_checkpoint_v2(db, NULL, SQLITE_CHECKPOINT_PASSIVE, pNumWalFrames, pNumCheckpointed);

    // Clean up
    sqlite3_close(db);
    free(pNumWalFrames);
    free(pNumCheckpointed);

    return 0;
}