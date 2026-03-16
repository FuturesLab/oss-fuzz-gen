#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

// This function will be used to test sqlite3_result_error_toobig
static void test_sqlite3_result_error_toobig(sqlite3_context *context) {
    // Call the sqlite3 function with the real context
    sqlite3_result_error_toobig(context);
}

// A simple SQLite function to be used with sqlite3_create_function
static void dummy_sql_function(sqlite3_context *context, int argc, sqlite3_value **argv) {
    // Directly test the function under test
    test_sqlite3_result_error_toobig(context);
}

extern int LLVMFuzzerTestOneInput_553(const uint8_t *data, size_t size) {
    sqlite3 *db = NULL;
    char *errMsg = NULL;

    // Open a new in-memory SQLite database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a new function in the SQLite database
    if (sqlite3_create_function(db, "dummy_function_553", 1, SQLITE_UTF8, NULL, dummy_sql_function, NULL, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Ensure the input data is null-terminated and non-empty for sqlite3_mprintf
    char *input_data = (char *)malloc(size + 1);
    if (input_data == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(input_data, data, size);
    input_data[size] = '\0';

    // Prepare a SQL statement using the fuzzer's input data
    char *sql = sqlite3_mprintf("SELECT dummy_function_553(%Q);", input_data);
    if (sql == NULL) {
        free(input_data);
        sqlite3_close(db);
        return 0;
    }

    // Execute the function to trigger the context and test the function under test
    if (sqlite3_exec(db, sql, NULL, NULL, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
    }

    // Free the allocated resources
    sqlite3_free(sql);
    free(input_data);

    // Close the SQLite database
    sqlite3_close(db);

    return 0;
}