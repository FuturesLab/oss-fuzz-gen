#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h> // Include for malloc and free

// Mock function to create a sqlite3_stmt for testing purposes
sqlite3_stmt* create_mock_stmt() {
    sqlite3_stmt *stmt = NULL;
    sqlite3 *db = NULL;
    const char *sql = "SELECT * FROM test WHERE id = ?1 AND name = ?2";

    // Open a connection to an in-memory database
    if (sqlite3_open(":memory:", &db) == SQLITE_OK) {
        // Prepare the SQL statement
        sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    }

    // Normally we would close the database connection, but for this mock,
    // we leave it open to keep the statement valid.
    return stmt;
}

int LLVMFuzzerTestOneInput_118(const uint8_t *data, size_t size) {
    sqlite3_stmt *stmt = create_mock_stmt();
    char *param_name = NULL;

    if (stmt == NULL || size == 0) {
        return 0;
    }

    // Allocate memory for the parameter name and ensure it is null-terminated
    param_name = (char *)malloc(size + 1);
    if (param_name == NULL) {
        return 0;
    }
    memcpy(param_name, data, size);
    param_name[size] = '\0';

    // Call the function-under-test
    int index = sqlite3_bind_parameter_index(stmt, param_name);

    // Clean up
    free(param_name);
    sqlite3_finalize(stmt);

    return 0;
}