#include <stddef.h>
#include <stdint.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_64(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    int rc;
    
    // Open an in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Call the function-under-test
    int autocommit_status = sqlite3_get_autocommit(db);

    // Clean up
    sqlite3_close(db);

    return 0;
}