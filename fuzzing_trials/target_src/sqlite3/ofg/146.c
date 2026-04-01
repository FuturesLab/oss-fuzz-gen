#include <stdint.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_146(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3 *db = NULL;
    char *zErrMsg = 0;
    int rc;
    int logFrameCount = 0;
    int checkpointCount = 0;

    // Open a new in-memory SQLite database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // If opening the database fails, exit early
    }

    // Create a simple table to ensure the database is not empty
    rc = sqlite3_exec(db, "CREATE TABLE test (id INT);", NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare a string for the schema name
    const char *schema = "main";

    // Prepare an integer for the checkpoint mode, using a value from the data if available
    int mode = (size > 0) ? data[0] % 4 : 0; // Mode should be between 0 and 3

    // Call the function-under-test
    sqlite3_wal_checkpoint_v2(db, schema, mode, &logFrameCount, &checkpointCount);

    // Close the database
    sqlite3_close(db);

    return 0;
}