#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stddef.h> // Include for size_t

int LLVMFuzzerTestOneInput_360(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int config_option;
    void *config_value;

    // Initialize SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Ensure that size is within a reasonable range for config_option
    config_option = (size > 0) ? (data[0] % 100) : 0; // Example: limit to 100 options

    // Allocate memory for config_value based on the input size
    config_value = malloc(size);
    if (config_value == NULL) {
        sqlite3_close(db);
        return 0; // Memory allocation failed
    }

    // Copy data to config_value
    for (size_t i = 0; i < size; i++) {
        ((uint8_t *)config_value)[i] = data[i];
    }

    // Ensure that the config_value is not NULL and has valid data
    // Here we can use the first byte of data to determine if we should set a specific option
    if (config_option == 0) {
        // Set a default or safe option if config_option is 0
        config_option = SQLITE_DBCONFIG_ENABLE_LOAD_EXTENSION; // Example option
    }

    // Call the function under test
    int result = sqlite3_db_config(db, config_option, config_value);

    // Clean up
    free(config_value);
    sqlite3_close(db);

    return result; // Return the result of the function call
}