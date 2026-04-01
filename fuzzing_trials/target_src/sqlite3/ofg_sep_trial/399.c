#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_399(const uint8_t *data, size_t size) {
    // Initialize variables for the function-under-test
    sqlite3 *db = NULL;
    char db_name[] = "test.db";
    int rc = sqlite3_open(db_name, &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure we have enough data to work with
    if (size < sizeof(int) + 1) {
        sqlite3_close(db);
        return 0;
    }

    // Extract an integer command from the data
    int command = *(int *)data;
    data += sizeof(int);
    size -= sizeof(int);

    // Use the remaining data as the filename
    char filename[256];
    size_t filename_len = size < sizeof(filename) - 1 ? size : sizeof(filename) - 1;
    memcpy(filename, data, filename_len);
    filename[filename_len] = '\0';

    // Prepare a buffer for the void* argument
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    // Call the function-under-test
    sqlite3_file_control(db, filename, command, buffer);

    // Clean up
    sqlite3_close(db);

    return 0;
}

#ifdef __cplusplus
}
#endif