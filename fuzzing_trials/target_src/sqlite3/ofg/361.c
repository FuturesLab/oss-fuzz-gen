#include <stdint.h>
#include <stdlib.h>
#include <stddef.h> // Include for size_t
#include <sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_361(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int config_option;
    void *config_value;

    // Initialize the SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Ensure the size is within a reasonable range for config_option
    if (size < sizeof(int)) {
        sqlite3_close(db);
        return 0; // Not enough data to proceed
    }

    // Use the first 4 bytes of data to determine the config_option
    config_option = *(int *)data;

    // Use the remaining data as the config_value, ensuring it's not NULL
    config_value = (void *)(data + sizeof(int));
    
    // Call the function under test
    int result = sqlite3_db_config(db, config_option, config_value);

    // Clean up
    sqlite3_close(db);

    return result;
}

#ifdef __cplusplus
}
#endif