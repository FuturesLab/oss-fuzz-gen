#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

// Dummy function to act as a callback
void my_function(sqlite3_context *context, int argc, sqlite3_value **argv) {
    // Do nothing
}

int LLVMFuzzerTestOneInput_385(const uint8_t *data, size_t size) {
    sqlite3 *db;
    int rc;
    const char *func_name = "my_function";
    int nArg = 1; // Number of arguments the function takes
    int eTextRep = SQLITE_UTF8; // Text encoding
    void *pApp = NULL; // Application data pointer

    // Initialize SQLite in-memory database
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        return 0;
    }

    // Ensure data is null-terminated for use as a function name
    char *func_name_from_data = (char *)malloc(size + 1);
    if (func_name_from_data == NULL) {
        sqlite3_close(db);
        return 0;
    }
    memcpy(func_name_from_data, data, size);
    func_name_from_data[size] = '\0';

    // Call the function-under-test
    sqlite3_create_function(db, func_name_from_data, nArg, eTextRep, pApp, my_function, NULL, NULL);

    // Clean up
    free(func_name_from_data);
    sqlite3_close(db);

    return 0;
}