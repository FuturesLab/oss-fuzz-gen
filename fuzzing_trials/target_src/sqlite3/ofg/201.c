#include <stddef.h>   // Include this for size_t
#include <stdint.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_201(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int statusOp;
    int currentValue;
    int highwaterValue;
    int resetFlag;
    int rc;

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure size is sufficient to extract parameters
    if (size < sizeof(int) * 2) {
        sqlite3_close(db);
        return 0;
    }

    // Extract parameters from data
    statusOp = ((int*)data)[0]; // Extracting first int from data
    resetFlag = ((int*)data)[1]; // Extracting second int from data

    // Call the function-under-test
    sqlite3_db_status(db, statusOp, &currentValue, &highwaterValue, resetFlag);

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}