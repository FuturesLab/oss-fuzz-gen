#include <stdint.h>
#include <stddef.h> // Include for size_t
#include <stdlib.h> // Include for NULL
#include <sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

// Fuzzing harness for the function-under-test
int LLVMFuzzerTestOneInput_352(const uint8_t *data, size_t size) {
    sqlite3 *srcDb = NULL;
    sqlite3 *destDb = NULL;
    sqlite3_backup *backup = NULL;
    int rc;

    // Initialize SQLite databases
    rc = sqlite3_open(":memory:", &srcDb);
    if (rc != SQLITE_OK) {
        return 0;
    }

    rc = sqlite3_open(":memory:", &destDb);
    if (rc != SQLITE_OK) {
        sqlite3_close(srcDb);
        return 0;
    }

    // Use the input data to create a table and insert data into the source database
    char *errMsg = NULL;
    rc = sqlite3_exec(srcDb, "CREATE TABLE IF NOT EXISTS fuzz_table(data BLOB);", NULL, NULL, &errMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(srcDb);
        sqlite3_close(destDb);
        return 0;
    }

    // Prepare an SQL statement to insert the fuzzing input data
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(srcDb, "INSERT INTO fuzz_table(data) VALUES(?);", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(srcDb);
        sqlite3_close(destDb);
        return 0;
    }

    // Bind the input data to the SQL statement
    sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);

    // Execute the SQL statement
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        sqlite3_close(srcDb);
        sqlite3_close(destDb);
        return 0;
    }

    // Create a backup object
    backup = sqlite3_backup_init(destDb, "main", srcDb, "main");
    if (backup == NULL) {
        sqlite3_close(srcDb);
        sqlite3_close(destDb);
        return 0;
    }

    // Call the function-under-test
    int pageCount = sqlite3_backup_pagecount(backup);

    // Finalize the backup process
    sqlite3_backup_finish(backup);

    // Close the databases
    sqlite3_close(srcDb);
    sqlite3_close(destDb);

    return 0;
}

#ifdef __cplusplus
}
#endif