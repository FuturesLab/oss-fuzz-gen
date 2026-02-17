#include <stdint.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

int LLVMFuzzerTestOneInput_320(const uint8_t *data, size_t size) {
    // Declare and initialize variables
    sqlite3 *db;
    char *err_msg = 0;

    // Open a temporary in-memory database

    // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 0 of sqlite3_open
    if (sqlite3_open((const char *)"r", &db) != SQLITE_OK) {
    // End mutation: Producer.REPLACE_ARG_MUTATOR


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
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 0; // Failed to create table
        }

        // Insert the input data into the table
        char insert_sql[256];

        // Begin mutation: Producer.APPEND_MUTATOR - Incorporated data flow from sqlite3_exec to sqlite3_prepare
        int ret_sqlite3_vtab_distinct_kgwvw = sqlite3_vtab_distinct(NULL);
        if (ret_sqlite3_vtab_distinct_kgwvw < 0){
        	return 0;
        }
        sqlite3_free((void *)db);

        int ret_sqlite3_prepare_scagi = sqlite3_prepare(db, (const char *)"r", ret_sqlite3_vtab_distinct_kgwvw, NULL, db);
        if (ret_sqlite3_prepare_scagi < 0){
        	return 0;
        }

        // End mutation: Producer.APPEND_MUTATOR

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

    // Begin mutation: Producer.REPLACE_FUNC_MUTATOR - Replaced function sqlite3_close with sqlite3_extended_errcode
    sqlite3_extended_errcode(db);
    // End mutation: Producer.REPLACE_FUNC_MUTATOR



    return 0;
}