#include <stdint.h>
#include <stddef.h>
#include <sqlite3.h>
#include <string.h>

// Mock function to open a database and prepare a blob for testing
sqlite3_blob* prepare_blob(const uint8_t *data, size_t size) {
    sqlite3 *db;
    sqlite3_blob *blob = NULL;
    const char *db_name = "test.db";
    const char *table_name = "test_table";
    const char *column_name = "test_column";
    int row_id = 1;

    // Open the database
    if (sqlite3_open(db_name, &db) != SQLITE_OK) {
        return NULL;
    }

    // Create table and insert data for testing
    char *err_msg = NULL;
    char create_table_sql[256];
    snprintf(create_table_sql, sizeof(create_table_sql),
             "CREATE TABLE IF NOT EXISTS %s (id INTEGER PRIMARY KEY, %s BLOB);",
             table_name, column_name);
    if (sqlite3_exec(db, create_table_sql, 0, 0, &err_msg) != SQLITE_OK) {
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return NULL;
    }

    char insert_sql[256];
    snprintf(insert_sql, sizeof(insert_sql),
             "INSERT OR REPLACE INTO %s (id, %s) VALUES (%d, ?);",
             table_name, column_name, row_id);
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0) != SQLITE_OK) {
        sqlite3_close(db);
        return NULL;
    }

    if (sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return NULL;
    }
    sqlite3_finalize(stmt);

    // Open the blob
    if (sqlite3_blob_open(db, "main", table_name, column_name, row_id, 0, &blob) != SQLITE_OK) {
        sqlite3_close(db);
        return NULL;
    }

    // Close the database connection
    sqlite3_close(db);

    return blob;
}

int LLVMFuzzerTestOneInput_90(const uint8_t *data, size_t size) {
    sqlite3_blob *blob = prepare_blob(data, size);
    if (blob == NULL) {
        return 0;
    }

    // Call the function-under-test
    int blob_size = sqlite3_blob_bytes(blob);

    // Optionally read from the blob to increase coverage
    uint8_t *buffer = (uint8_t *)malloc(blob_size);
    if (buffer != NULL) {
        if (sqlite3_blob_read(blob, buffer, blob_size, 0) == SQLITE_OK) {
            // Process buffer if needed
        }
        free(buffer);
    }

    // Clean up
    sqlite3_blob_close(blob);

    return 0;
}