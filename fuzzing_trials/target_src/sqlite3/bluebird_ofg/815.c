#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <stdlib.h>
#include <sys/stat.h>  // Include for NULL
#include "sqlite3.h"

int LLVMFuzzerTestOneInput_815(const uint8_t *data, size_t size) {
    // Initialize SQLite3 and create a memory database
    sqlite3 *db;
    if (sqlite3_open(":memory:", &db) != SQLITE_OK) {
        return 0;  // If opening the database fails, return early
    }

    // Create a table
    char *errMsg = NULL;
    if (sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS fuzz_table (data BLOB);", NULL, NULL, &errMsg) != SQLITE_OK) {
        sqlite3_free(errMsg);
        sqlite3_close(db);
        return 0;
    }

    // Prepare an insert statement
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, "INSERT INTO fuzz_table (data) VALUES (?);", -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        return 0;  // If preparing the statement fails, clean up and return early
    }

    // Bind the input data to the statement as a BLOB
    if (sqlite3_bind_blob(stmt, 1, data, (int)size, SQLITE_TRANSIENT) != SQLITE_OK) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;  // If binding the blob fails, clean up and return early
    }

    // Execute the statement to insert the data
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;  // If execution fails, clean up and return early
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

    LLVMFuzzerTestOneInput_815(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
