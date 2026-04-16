#include <stdint.h>
#include <stddef.h>  // Include for size_t
#include <stdlib.h>
#include <sys/stat.h>  // Include for NULL
#include "sqlite3.h"
#include <string.h>  // Include for memcpy

int LLVMFuzzerTestOneInput_740(const uint8_t *data, size_t size) {
    sqlite3_mutex *mutex;
    sqlite3 *db;
    char *errMsg = 0;
    int rc;
    const char *sql;

    // Initialize the SQLite library
    if (sqlite3_initialize() != SQLITE_OK) {
        return 0;
    }

    // Allocate a mutex
    mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
    if (mutex == NULL) {
        return 0;
    }

    // Simulate using the input data to influence the function-under-test
    if (size > 0) {
        // Create an in-memory database
        rc = sqlite3_open(":memory:", &db);
        if (rc) {
            sqlite3_mutex_free(mutex);
            sqlite3_shutdown();
            return 0;
        }

        // Dummy SQL statement that uses input data
        sql = "CREATE TABLE IF NOT EXISTS fuzz_table(data BLOB);";
        rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            sqlite3_free(errMsg);
            sqlite3_close(db);
            sqlite3_mutex_free(mutex);
            sqlite3_shutdown();
            return 0;
        }

        // Insert the input data into the table
        sqlite3_mutex_enter(mutex);
        sqlite3_stmt *stmt;
        sql = "INSERT INTO fuzz_table (data) VALUES (?);";
        rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
        if (rc == SQLITE_OK) {
            sqlite3_bind_blob(stmt, 1, data, size, SQLITE_STATIC);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
        sqlite3_mutex_leave(mutex);

        // Clean up
        sqlite3_close(db);
    }

    // Call the function-under-test
    sqlite3_mutex_free(mutex);

    // Deinitialize the SQLite library
    sqlite3_shutdown();

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

    LLVMFuzzerTestOneInput_740(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
