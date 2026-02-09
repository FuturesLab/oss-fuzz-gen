#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_97(const uint8_t *data, size_t size) {
    // Initialize variables
    sqlite3 *db = NULL;
    int checkpoint_value = 0;

    // Open a new SQLite database in memory
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Ensure the size is within a reasonable range for the checkpoint value
    if (size > sizeof(int)) {
        checkpoint_value = *((int *)data) % 100; // Use modulo to keep it within a reasonable range
    } else {
        checkpoint_value = (int)data[0]; // Use the first byte as the checkpoint value
    }

    // Call the function under test
    int result = sqlite3_wal_autocheckpoint(db, checkpoint_value);

    // Clean up
    sqlite3_close(db);

    return 0;
}