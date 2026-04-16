#include <stdint.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int LLVMFuzzerTestOneInput_379(const uint8_t *data, size_t size) {
    // Initialize SQLite database in memory
    sqlite3 *db;
    sqlite3_open(":memory:", &db);

    // Create a simple table
    const char *create_table_sql = "CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT);";
    sqlite3_exec(db, create_table_sql, 0, 0, 0);

    // Prepare an insert statement
    sqlite3_stmt *stmt;
    const char *insert_sql = "INSERT INTO test (value) VALUES (?);";
    sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);

    // Bind fuzzing data as a text value
    sqlite3_bind_text(stmt, 1, (const char *)data, size, SQLITE_TRANSIENT);

    // Execute the insert statement
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    // Prepare a select statement
    const char *select_sql = "SELECT value FROM test WHERE id = 1;";
    sqlite3_prepare_v2(db, select_sql, -1, &stmt, 0);

    // Execute the select statement
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        // Call the function-under-test
        int bytes16 = sqlite3_column_bytes16(stmt, 0);
    }

    // Finalize the statement and close the database
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

    LLVMFuzzerTestOneInput_379(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
