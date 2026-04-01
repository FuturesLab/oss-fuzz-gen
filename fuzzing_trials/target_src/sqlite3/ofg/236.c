#include <stdint.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput_236(const uint8_t *data, size_t size) {
    // Ensure there's enough data for the function call
    if (size < sizeof(int)) {
        return 0;
    }

    // Initialize SQLite
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Extract an integer from the data to use as the configuration option
    int config_option = *(int *)data;
    data += sizeof(int);
    size -= sizeof(int);

    // Create a non-NULL pointer for the void* parameter
    void *param = (void *)data;

    // Call the function-under-test
    sqlite3_vtab_config(db, config_option, param);

    // Clean up
    sqlite3_close(db);

    return 0;
}