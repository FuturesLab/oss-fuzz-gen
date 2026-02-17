#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>

int LLVMFuzzerTestOneInput_96(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int checkpoint_value;

    // Initialize SQLite database
    int rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0; // Unable to open database
    }

    // Ensure the checkpoint_value is a valid integer
    // Use the first 4 bytes of data to create a valid integer
    if (size >= sizeof(int)) {
        checkpoint_value = *(int*)data; // Cast the first 4 bytes to an int
    } else {
        checkpoint_value = 0; // Default value if data is too small
    }

    // Call the function under test
    sqlite3_wal_autocheckpoint(db, checkpoint_value);

    // Close the database
    sqlite3_close(db);

    return 0;
}