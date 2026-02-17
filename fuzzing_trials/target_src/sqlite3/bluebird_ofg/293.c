#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#ifdef __cplusplus
extern "C" {
#endif

int LLVMFuzzerTestOneInput_293(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    char *errMsg = NULL;
    int result;

    // Initialize SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Create a simple SQL statement using the input data
    // Ensure the data is null-terminated for use in SQL
    char *sql = (char *)malloc(size + 1);
    if (sql == NULL) {

        // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_total_changes
        sqlite3_total_changes(db);
        // End mutation: Producer.REPLACE_FUNC_MUTATOR


        return 0; // Memory allocation failed
    }
    memcpy(sql, data, size);
    sql[size] = '\0'; // Null-terminate the string

    // Execute the SQL statement
    result = sqlite3_exec(db, sql, NULL, 0, &errMsg);
    if (result != SQLITE_OK) {
        sqlite3_free(errMsg); // Free error message if there was one
    }

    // Clean up
    free(sql);
    sqlite3_close(db);

    return result; // Return the result of the function call
}
#ifdef __cplusplus
}
#endif