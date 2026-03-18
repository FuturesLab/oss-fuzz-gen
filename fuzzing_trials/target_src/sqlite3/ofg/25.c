#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

int LLVMFuzzerTestOneInput_25(const uint8_t *data, size_t size) {
    // Ensure that the input data is null-terminated
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Call the function-under-test: open a SQLite database
    sqlite3 *db;
    int rc = sqlite3_open(input_data, &db);

    // If the database was opened successfully, close it
    if (rc == SQLITE_OK) {
        sqlite3_close(db);
    }

    // Clean up
    free(input_data);

    return 0;
}