#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_368(const uint8_t *data, size_t size) {
    // Check if the input data is not null and has a valid size
    if (data == NULL || size == 0) {
        return 0;
    }

    // Initialize SQLite
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;
    }

    // Create a statement to use sqlite3_value
    sqlite3_stmt *stmt;
    const char *sql = "CREATE TABLE IF NOT EXISTS fuzz_table (data BLOB);";
    if (sqlite3_exec(db, sql, NULL, NULL, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Insert the input data into the table
    sql = "INSERT INTO fuzz_table (data) VALUES (?);";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Bind the input data to the statement as a blob
    if (sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Execute the statement
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Query the data back to ensure it was inserted
    sql = "SELECT data FROM fuzz_table;";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;
    }

    // Step to the first result row
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Get the sqlite3_value from the statement
        const unsigned char *text = sqlite3_column_text(stmt, 0);

        // Use the result to prevent optimization out
        if (text) {
            volatile unsigned char dummy = text[0];
            (void)dummy;
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_368(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
