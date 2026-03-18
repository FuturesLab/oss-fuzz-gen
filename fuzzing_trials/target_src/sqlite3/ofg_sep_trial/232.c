#include <stddef.h>  // Include for size_t
#include <stdint.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_232(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    int configOption;
    void *pArg;

    // Initialize SQLite database in memory
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure size is sufficient to extract configOption and pArg
    if (size < sizeof(int) + sizeof(void *)) {
        sqlite3_close(db);
        return 0;
    }

    // Extract configOption and pArg from data
    configOption = *(int *)data;
    pArg = (void *)(data + sizeof(int));

    // Call the function-under-test
    sqlite3_vtab_config(db, configOption, pArg);

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}