#include <sqlite3.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    // Initialize SQLite
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Create a dummy statement
    const char *sql = "SELECT * FROM test WHERE column = ?";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    // Ensure data is null-terminated for use as a string
    char *param_name = (char *)malloc(size + 1);
    if (param_name == NULL) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }
    memcpy(param_name, data, size);
    param_name[size] = '\0';

    // Call the function-under-test
    int index = sqlite3_bind_parameter_index(stmt, param_name);

    // Clean up
    free(param_name);
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}