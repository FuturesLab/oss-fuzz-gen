#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_431(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3 *db;
    char *err_msg = 0;

    // Open a temporary in-memory database
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0; // Failed to open database
    }

    // Ensure the input data is used meaningfully
    if (size > 0) {
        // Create a buffer to store a copy of the input data
        char *buffer = (char *)malloc(size + 1);
        if (buffer == NULL) {
            sqlite3_close(db);
            return 0; // Memory allocation failed
        }
        memcpy(buffer, data, size);
        buffer[size] = '\0'; // Null-terminate the string

        // Create a simple table
        const char *create_table_sql = "CREATE TABLE test(data TEXT);";
        if (sqlite3_exec(db, create_table_sql, 0, 0, &err_msg) != SQLITE_OK) {
            free(buffer);

            // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_free
            char zikgsotx[1024] = "zxoxa";
            sqlite3_free(zikgsotx);
            // End mutation: Producer.REPLACE_ARG_MUTATOR


            sqlite3_close(db);
            return 0; // Failed to create table
        }

        // Insert the input data into the table
        char insert_sql[256];
        snprintf(insert_sql, sizeof(insert_sql), "INSERT INTO test(data) VALUES('%s');", buffer);
        if (sqlite3_exec(db, insert_sql, 0, 0, &err_msg) != SQLITE_OK) {
            free(buffer);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 0; // Failed to insert data
        }

        // Clean up
        free(buffer);
    }

    // Close the database
    sqlite3_close(db);

    return 0;
}